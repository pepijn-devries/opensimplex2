test_that("simplex2d is reproducible", {
  ## TODO not sure if this test with doubles calculation is too accurate
  announce_snapshot_file(name = "simplex2s.rdata")
  mat <- simplex2d(100, 100, 1)
  fn <- tempfile(fileext = ".rdata")
  save(mat, file = fn, compress = TRUE)
  expect_snapshot_file(fn, "simplex2d.rdata", compare = \(old, new) {
    load(old)
    mat_old <- mat
    load(new)
    all((mat - mat_old) < 1e-4)
  })
})