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

test_that("Noise properties are as intended", {
  skip_on_cran()
  expect_true({
    dim_names <- c("width", "height", "depth", "slice")
    dim_size  <- 30
    mns <- numeric(0)
    sds <- numeric(0)
    for (type in c("F", "S")) {
      for (dimensions in 2:4) {
        args <-
          structure(rep(dim_size, dimensions), names = dim_names[1:dimensions]) |>
          as.list() |>
          c(type = type, frequency = 3)
        mat <- do.call(opensimplex_noise, args)
        ## check all slices in the array
        for (dimension  in 1:dimensions) {
          idx <- slice.index(mat, dimension)
          for (i in seq_len(max(idx))) {
            ## Data at specific slice:
            test_data <- mat[idx == i]
            test_slice <-
              min(test_data) >= -1 &&
              max(test_data) <= 1 &&
              abs(mean(test_data)) < 0.1 &&
              sd(test_data) > 0.1
            mns <- c(mns, mean(test_data)*dimension)
            sds <- c(sds, sd(test_data)*dimension)
          }
        }
      }
    }
    means_range <- abs(mns) < .5
    means_range <- length(means_range[means_range])/ length(means_range)
    sds_range   <- abs(sds - .8) < .4
    sds_range   <- length(sds_range[sds_range])/ length(sds_range)
    means_range > .95 && sds_range > .7
  })
})

test_that("OpenSimplex space has different time when seed is not set", {
  expect_true({
    result <- TRUE
    for (type in c("F", "S")) {
      for (dimensions in 2:4) {
        space1 <- opensimplex_space(type, dimensions)
        space2 <- opensimplex_space(type, dimensions)
        coords <- lapply(seq_len(dimensions), \(i) runif(100, -100, 100)) |>
          setNames(letters[8 + seq_len(dimensions)])
        noise1 <- do.call(space1$sample, coords)
        noise2 <- do.call(space2$sample, coords)
        result <- result && !identical(noise1, noise2)
      }
    }
    result
  })
})