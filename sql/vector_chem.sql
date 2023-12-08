-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION vector_chem" to load this file. \quit

-- functions

CREATE FUNCTION tanimoto_distance(vector, vector) RETURNS float8
	AS 'MODULE_PATHNAME' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

-- operators

CREATE OPERATOR <^> (
	LEFTARG = vector, RIGHTARG = vector, PROCEDURE = tanimoto_distance,
	COMMUTATOR = '<^>'
);

-- opclasses

CREATE OPERATOR CLASS vector_tanimoto_ops
	FOR TYPE vector USING hnsw AS
	OPERATOR 1 <^> (vector, vector) FOR ORDER BY float_ops,
	FUNCTION 1 tanimoto_distance(vector, vector);
