#' @keywords internal
"_PACKAGE"

## usethis namespace: start
#' @useDynLib opensimplex2, .registration = TRUE
## usethis namespace: end
NULL

.onUnload <- function(libpath) {
  ## Unload the dynamic binding (particularly useful on Windows)
  library.dynam.unload("opensimplex2", libpath)
}
