#' TODO
#' 
#' TODO
#' @param width,height TODO
#' @param frequency TODO
#' @param seed TODO
#' @returns TODO
#' @examples
#' mat <- simplex2d(100, 100, 1)
#' image(mat)
#' @export
simplex2d <- function(width, height, frequency = 1, seed = 0L) {
  noise2d_(width, height, frequency, seed)
}