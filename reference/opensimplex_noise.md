# TODO

TODO

## Usage

``` r
opensimplex_noise(type = "S", width, height, depth, slice, frequency = 1)
```

## Arguments

- type:

  TODO

- width, height, depth, slice:

  TODO

- frequency:

  TODO

## Value

A `matrix` (in case of two dimensions) or `array` (in case of more
dimensions) of `numeric` values between -1 and +1. TODO

## Examples

``` r
mat <- opensimplex_noise("S", 100, 100)
image(mat)
```
