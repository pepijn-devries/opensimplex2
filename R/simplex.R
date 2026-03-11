#' TODO
#' 
#' TODO
#' @param width,height TODO
#' @param frequency TODO
#' @param seed TODO
#' @returns TODO
#' @examples
#' mat <- simplex2d(100, 100)
#' image(mat)
#' @export
simplex2d <- function(width, height, frequency = 1, seed = 0L) {
  noise2d_(width, height, frequency, seed)
}

#' TODO
#' 
#' TODO
#' @param width,height,depth TODO
#' @param frequency TODO
#' @param seed TODO
#' @returns TODO
#' @examples
#' mat <- simplex3d(100, 100, 100)
#' image(mat[,,1])
#' @export
simplex3d <- function(width, height, depth, frequency = 1, seed = 0L) {
  noise3d_(width, height, depth, frequency, seed)
}