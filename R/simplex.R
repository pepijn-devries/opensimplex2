#' TODO
#' 
#' TODO
#' @param width,height TODO
#' @param frequency TODO
#' @returns TODO
#' @examples
#' mat <- simplex2d(100, 100)
#' image(mat)
#' @export
simplex2d <- function(width, height, frequency = 1) {
  noise2d_(width, height, frequency)
}

#' TODO
#' 
#' TODO
#' @param width,height,depth TODO
#' @param frequency TODO
#' @returns TODO
#' @examples
#' mat <- simplex3d(100, 100, 100)
#' image(mat[,,1])
#' @export
simplex3d <- function(width, height, depth, frequency = 1) {
  noise3d_(width, height, depth, frequency)
}

#' TODO
#' 
#' TODO
#' @param width,height,depth,slice TODO
#' @param frequency TODO
#' @returns TODO
#' @examples
#' mat <- simplex4d(25, 25, 25, 25)
#' image(mat[,,1,1])
#' @export
simplex4d <- function(width, height, depth, slice, frequency = 1) {
  noise4d_(width, height, depth, slice, frequency)
}