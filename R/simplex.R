#' TODO
#' 
#' TODO
#' @param type TODO
#' @param width,height,depth,slice TODO
#' @param frequency TODO
#' @returns A `matrix` (in case of two dimensions) or `array` (in case of more
#' dimensions) of `numeric` values between -1 and +1. TODO
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

#' TODO
#' 
#' TODO
#' @param type TODO
#' @param dimensions TODO
#' @returns TODO
#' @examples
#' # TODO
#' 
#' @export
opensimplex_space <- function(type = "S", dimensions = 2L) {
  dimensions <- as.integer(dimensions)
  oss <- simplex_space_(type, dimensions)
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
    close = function() {
      invisible(simplex_sample_close(oss))
    })
}
