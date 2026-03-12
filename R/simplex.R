#' TODO
#' 
#' TODO
#' @param type TODO
#' @param width,height,depth,slice TODO
#' @param frequency TODO
#' @returns TODO
#' @examples
#' mat <- opensimplex_noise("F", 100, 100)
#' image(mat)
#' @export
opensimplex_noise <- function(type = "F", width, height, depth, slice, frequency = 1) {
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
      noise3d_(width, height, depth, frequency)
    } else {
      noise4d_(width, height, depth, slice, frequency)
    }
  }
}