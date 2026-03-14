# opensimplex2

TODO

## Installation

TODO

``` r
# TODO
```

## Example

TODO

``` r
library(opensimplex2)
## Set seed to obtain reproducible data
set.seed(0)
## Create simplex noise in 3 dimensions:
arr <- opensimplex_noise("S", 100, 100, 100, frequency = 1.5)

## Plot 2D noise while looping the third dimension:
for (i in 1:100) {
  image(arr[,,i],
        axes = FALSE, ann = FALSE, xaxs = "i", yaxs = "i",
        zlim = c(-1, +1), col = hcl.colors(palette = "Terrain", 10))
}
```

![](reference/figures/README-example-.gif)

## Acknowledgments

This package wraps the C-code by [Marco
Ciaramella](https://github.com/MarcoCiaramella/opensimplex2), which in
turn is a translation of the original Java code by
[KdotJPG](https://github.com/KdotJPG/OpenSimplex2).

## Code of Conduct

Please note that the opensimplex2 project is released with a
[Contributor Code of
Conduct](https://contributor-covenant.org/version/2/1/CODE_OF_CONDUCT.html).
By contributing to this project, you agree to abide by its terms.
