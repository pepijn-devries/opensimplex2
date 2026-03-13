compare_results <- function(old, new) {
  load(old)
  mat_old <- mat
  rm(mat)
  load(new)
  !any(abs(c(mat) - c(mat_old)) > 1e-5)
}

test_that("opensimplex F 2D is reproducible", {
  fn <- "simplexF2D.rdata"
  set.seed(0)
  mat <- opensimplex_noise("F", 100, 100, frequency = 1)
  fn_new <- tempfile(fileext = ".rdata")
  on.exit({unlink(fn_new)})
  save(mat, file = fn_new, compress = TRUE)
  announce_snapshot_file(fn)
  testthat::expect_snapshot_file(fn_new, fn, compare = compare_results)
})

test_that("opensimplex F 3D is reproducible", {
  fn <- "simplexF3D.rdata"
  set.seed(0)
  mat <- opensimplex_noise("F", 20, 20, 20, frequency = 1)
  fn_new <- tempfile(fileext = ".rdata")
  on.exit({unlink(fn_new)})
  save(mat, file = fn_new, compress = TRUE)
  announce_snapshot_file(fn)
  testthat::expect_snapshot_file(fn_new, fn, compare = compare_results)
})

test_that("opensimplex F 4D is reproducible", {
  fn <- "simplexF4D.rdata"
  set.seed(0)
  mat <- opensimplex_noise("F", 10, 10, 10, 10, frequency = 1)
  fn_new <- tempfile(fileext = ".rdata")
  on.exit({unlink(fn_new)})
  save(mat, file = fn_new, compress = TRUE)
  announce_snapshot_file(fn)
  testthat::expect_snapshot_file(fn_new, fn, compare = compare_results)
})

test_that("opensimplex S 2D is reproducible", {
  fn <- "simplexS2D.rdata"
  set.seed(0)
  mat <- opensimplex_noise("S", 100, 100, frequency = 1)
  fn_new <- tempfile(fileext = ".rdata")
  on.exit({unlink(fn_new)})
  save(mat, file = fn_new, compress = TRUE)
  announce_snapshot_file(fn)
  testthat::expect_snapshot_file(fn_new, fn, compare = compare_results)
})

test_that("opensimplex S 3D is reproducible", {
  fn <- "simplexS3D.rdata"
  set.seed(0)
  mat <- opensimplex_noise("S", 20, 20, 20, frequency = 1)
  fn_new <- tempfile(fileext = ".rdata")
  on.exit({unlink(fn_new)})
  save(mat, file = fn_new, compress = TRUE)
  announce_snapshot_file(fn)
  testthat::expect_snapshot_file(fn_new, fn, compare = compare_results)
})

test_that("opensimplex S 4D is reproducible", {
  fn <- "simplexS4D.rdata"
  set.seed(0)
  mat <- opensimplex_noise("S", 10, 10, 10, 10, frequency = 1)
  fn_new <- tempfile(fileext = ".rdata")
  on.exit({unlink(fn_new)})
  save(mat, file = fn_new, compress = TRUE)
  announce_snapshot_file(fn)
  testthat::expect_snapshot_file(fn_new, fn, compare = compare_results)
})