test_that("simplex2d is acceptable", {
  expect_true({
    mat <- simplex2d(100, 100, 1)
    test1 <- max(abs(mat[-1,] - mat[-100,])) < .2
    test2 <- all(mat >= -1) && all(mat <= 1)
    test1 && test2
  })
})