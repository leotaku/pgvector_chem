#include "postgres.h"

#include "catalog/pg_type.h"
#include "fmgr.h"
#include "vector.h"

PG_MODULE_MAGIC;

/*
 * Ensure same dimensions
 */
static inline void
CheckDims(Vector * a, Vector * b)
{
	if (a->dim != b->dim)
		ereport(ERROR,
				(errcode(ERRCODE_DATA_EXCEPTION),
				 errmsg("different vector dimensions %d and %d", a->dim, b->dim)));
}

/*
 * Get the tanimoto distance between two vectors of binary values
 * Assumes inputs are binary vectors
 */
PGDLLEXPORT PG_FUNCTION_INFO_V1(tanimoto_distance);
Datum
tanimoto_distance(PG_FUNCTION_ARGS)
{
	Vector	   *a = PG_GETARG_VECTOR_P(0);
	Vector	   *b = PG_GETARG_VECTOR_P(1);
	float	   *ax = a->x;
	float	   *bx = b->x;
	float		tania = 0.0;
	float		tanib = 0.0;
	float		tanic = 0.0;
	double		similarity;

	CheckDims(a, b);

	/* Auto-vectorized */
	for (int i = 0; i < a->dim; i++)
	{
		tania += ax[i];
		tanib += bx[i];
        tanic += ax[i] * bx[i];
	}

	/* Use sqrt(a * b) over sqrt(a) * sqrt(b) */
	similarity = (double) tanic / ((double) tania + (double) tanib - (double) tanic) ;

#ifdef _MSC_VER
	/* /fp:fast may not propagate NaN */
	if (isnan(similarity))
		PG_RETURN_FLOAT8(NAN);
#endif

	PG_RETURN_FLOAT8(1.0 - similarity);
}
