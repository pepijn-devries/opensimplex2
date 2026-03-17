.doc_seed_text <- function() {
  c(
    "The exact state of the noise gradient space depends on R's internal",
    "random generator. So each time you call `opensimplex_space`, you will get a",
    "space in a different state. If you want to obtain a reproducible state,",
    "you simply set the random seed with [`set.seed()`]."
  )
}

#' Get a 2, 3, or 4 Dimensional Array of Simplex Noise
#' 
#' Create a regular n-dimensional grid with an OpenSimplex2 noise gradient.
#' You can control the noisiness to some degree with the `frequency` argument.
#' If you want more control, you should use [`opensimplex_sample`], which
#' allows you to create a continuous OpenSimplex noise gradient space,
#' that can be sampled at any arbitrary coordinate.
#' 
#' `r .doc_seed_text()`
#' @param type Type of OpenSimplex2 you wish to use. Should be either
#' `"F"` for fast or `"S"` for smooth.
#' @param width,height,depth,slice Positive `integer` size of each of the
#' desired dimensions. `width` and `height` dimensions are required. Other
#' dimensions are optional. However, `depth` is required when `slice` dimension
#' is specified.
#' @param frequency The frequency (`numeric`) with which the noise gradient fluctuates
#' with respect to each respective dimension. Low values (<1) will generate
#' smooth gradients, whereas large values (>1) will result in very noisy
#' gradients. Default value is 1.
#' @returns A `matrix` (in case of two dimensions) or `array` (in case of more
#' dimensions) of `numeric` values between -1 and +1. OpenSimplex2 uses
#' gradient tables that ensure that the distribution of values is centred at zero,
#' meaning the "peaks" and "valleys" are statistically balanced.
#' @examples
#' mat <- opensimplex_noise("S", 100, 100)
#' image(mat)
#' @export
opensimplex_noise <- function(type = "S", width, height, depth, slice, frequency = 1) {
  type <- match.arg(type, c("F", "S"))
  if (missing(depth)) {
    if (missing(slice)) {
      if (type == "F") {
        noise2d_(width, height, frequency)
      } else {
        noise2dS_(width, height, frequency)
      }
    } else {
      stop("Argument 'depth' should not be missing when 'slice' is specified.")
    }
  } else {
    if (missing(slice)) {
      if (type == "F") {
        noise3d_(width, height, depth, frequency)
      } else {
        noise3dS_(width, height, depth, frequency)
      }
    } else {
      if (type == "F") {
        noise4d_(width, height, depth, slice, frequency)
      } else {
        noise4dS_(width, height, depth, slice, frequency)
      }
    }
  }
}

#' Get a 2, 3, or 4 Dimensional OpenSimplex Noise Gradient Field
#' 
#' Create a continuous OpenSimplex noise gradient space, that can be sampled
#' at any arbitrary coordinate. The gradient has `numeric` values between -1
#' and +1. OpenSimplex2 uses gradient tables that ensure that the distribution
#' of values is centred at zero, meaning the "peaks" and "valleys" are
#' statistically balanced.
#'  
#' `r .doc_seed_text()`
#' @inheritParams opensimplex_noise
#' @param dimensions An integer value of number of dimensions to be used in your gradient
#' space. Should be 2, 3 or 4.
#' @returns Returns a named `list`. It has the elements:
#'  * *`sample`*: which is a function that will return the simplex noise value (between -1 and +1)
#'    at a given coordinate. The function takes the same number of arguments as the value of
#'    `dimensions`. Each argument is a coordinate in the \ifelse{html}{\out{n<sup>th</sup>}}{\eqn{n^{th}}{n^th}}
#'    dimension. You can provide multiple coordinates, as long as you provide the same
#'    number of coordinates in each dimension.
#'  * *`dimensions`*: an integer value indicating the number of dimensions
#'    available in this space object.
#'  * *`type`*: A `character` string indicating whether this object uses the fast
#'    (`"F"`) or smooth (`"S"`) variant of OpenSimplex2.
#'  * *`close`*: which is a function that closes the simplex noise gradient space. In other words, memory
#'    used to specify the gradient space is freed, and can no longer be accessed. After closing
#'    the space, you can no longer `sample` it.
#' @examples
#' ## By setting a random generator seed, the example below becomes reproducible
#' set.seed(0)
#' 
#' ## Open a extra smooth ("S") simplex noise gradient with 3 dimensions:
#' space <- opensimplex_space("S", 3L)
#' 
#' ## Sample it at some random coordinates
#' space$sample(i = 5*runif(10), j = 10*runif(10), k = 15*runif(10))
#' 
#' ## Close it when you are done
#' space$close()
#' @export
opensimplex_space <- function(type = "S", dimensions = 2L) {
  dimensions <- as.integer(dimensions)
  oss <- simplex_space_(type, dimensions)
  result <-
    list(
      sample = switch(
        LETTERS[dimensions],
        B = {
          function(i, j) {
            simplex_sample_space_2d(oss, as.double(i), as.double(j))
          }
        },
        C = {
          function(i, j, k) {
            simplex_sample_space_3d(oss, as.double(i), as.double(j), as.double(k))
          }
        },
        D = {
          function(i, j, k, l) {
            simplex_sample_space_4d(oss, as.double(i), as.double(j), as.double(k), as.double(l))
          }
        },
        stop("Dimensions out of range")),
      dimensions = dimensions,
      type = type,
      close = function() {
        invisible(simplex_sample_close(oss))
      })
  class(result) <- "opensimplex_space"
  result
}

#' @exportS3Method base::print
print.opensimplex_space <- function(x, ...) {
  idx <- paste(letters[8 + seq_len(x$dimensions)], collapse = ", ")
  msg <- paste(
    sprintf("A '%s' %i-dimensional simplex gradient noise space object.",
            ifelse(x$type == "F", "fast", "smooth"), x$dimensions),
    sprintf("Use its element .$sample(%s) to sample it.", idx),
    sep = "\n")
  cat(msg)
}

.assign_error <- function() {
  stop("You cannot assign data to an opensimplex_space class object")
}

#' @export
`$<-.opensimplex_space` <- function(x, name, value) {
  .assign_error()
}

#' @export
`[<-.opensimplex_space` <- function(x, i, value) {
  .assign_error()
}

#' @export
`[[<-.opensimplex_space` <- function(x, i, value) {
  .assign_error()
}