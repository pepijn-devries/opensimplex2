# Get a 2, 3, or 4 Dimensional OpenSimplex Noise Gradient Field

Create a continuous OpenSimplex noise gradient space, that can be
sampled at any arbitrary coordinate. The gradient has `numeric` values
between -1 and +1. OpenSimplex2 uses gradient tables that ensure that
the distribution of values is centred at zero, meaning the "peaks" and
"valleys" are statistically balanced.

The exact state of the noise gradient space depends on R's internal,
random generator. So each time you call `opensimplex_space`, you will
get a, space in a different state. If you want to obtain a reproducible
state,, you simply set the random seed with
[`set.seed()`](https://rdrr.io/r/base/Random.html).

## Usage

``` r
opensimplex_space(type = "S", dimensions = 2L)
```

## Arguments

- type:

  Type of OpenSimplex2 you wish to use. Should be either `"F"` for fast
  or `"S"` for smooth.

- dimensions:

  An integer value of number of dimensions to be used in your gradient
  space. Should be 2, 3 or 4.

## Value

Returns a named `list`. It has the elements:

- *`sample`*: which is a function that will return the simplex noise
  value (between -1 and +1) at a given coordinate. The function takes
  the same number of arguments as the value of `dimensions`. Each
  argument is a coordinate in the n^(th) dimension. You can provide
  multiple coordinates, as long as you provide the same number of
  coordinates in each dimension.

- *`dimensions`*: an integer value indicating the number of dimensions
  available in this space object.

- *`type`*: A `character` string indicating whether this object uses the
  fast (`"F"`) or smooth (`"S"`) variant of OpenSimplex2.

- *`close`*: which is a function that closes the simplex noise gradient
  space. In other words, memory used to specify the gradient space is
  freed, and can no longer be accessed. After closing the space, you can
  no longer `sample` it.

## Examples

``` r
## By setting a random generator seed, the example below becomes reproducible
set.seed(0)

## Open a extra smooth ("S") simplex noise gradient with 3 dimensions:
space <- opensimplex_space("S", 3L)

## Sample it at some random coordinates
space$sample(i = 5*runif(10), j = 10*runif(10), k = 15*runif(10))
#>  [1] -0.025858678 -0.308269378 -0.565530755 -0.228776258  0.382789119
#>  [6] -0.203858608  0.007291668 -0.328228602  0.304160169  0.131660417

## Close it when you are done
space$close()
```
