# pgvector_chem

Distance metrics used in chemoinformatics domains for Postgres [pgvector][pgvector]. Provides:

+ Tanimoto/Jaccard-Index for dichotomous values

## Installation

```shell
git clone https://github.com/leotaku/pgvector_chem
cd pgvector_chem
make CC=cc && make install
```

## Usage

### Setup

In order to use the functionality provided by this extension first install and enable the [pgvector][pgvector] extension.

```tsql
CREATE EXTENSION vector;
```

Enable the extension (do this once in each database where you want to use it).

```tsql
CREATE EXTENSION vector_chem;
```

### Querying

We define the operator `<^>` for computing the Tanimoto distance between two vectors of dichotomous values.

```tsql
SELECT '[1., 0., 1.]' <^> '[1., 0., 1.]';
-- ?column?
-- ----------
--       0
-- (1 row)
```

The function `tanimoto_distance` is also defined and computes the same result as the `<^>` operator.

```tsql
SELECT tanimoto_distance('[1., 0., 1.]', '[1., 0., 0.]');
--  tanimoto_distance
-- -------------------
--                0.5
-- (1 row)
```

## FAQ

### Should I use this library?

Unless you need to support the Tanimoto/Jaccard-Index for historical reasons, you are probably better served by the cosine distance (`<=>`) built in to [pgvector][pgvector].

Cosine distance has been shown to carry essentially the same information as Tanimoto/Jaccard in a wide range of applications.[<sup>1</sup>][bajusz2015]

### Is the provided Tanimoto/Jaccard-Index distance usable for continuous values?

Not at this time.

### Is approximate nearest neighbor search supported?

Not at this time.

[pgvector]: https://github.com/pgvector/pgvector#pgvector
[bajusz2015]: https://jcheminf.biomedcentral.com/articles/10.1186/s13321-015-0069-3

