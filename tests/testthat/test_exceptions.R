test_that("You cannot assign values to opensimplex_space objects", {
  expect_error({
    space <- opensimplex_space()
    space$dimensions <- 1L
  }, "You cannot assign data to an opensimplex_space")
})

test_that("You cannot assign values to opensimplex_space objects", {
  expect_no_error({
    space <- opensimplex_space()
    print(space)
  })
})

test_that(".doc_seed_text is characters", {
  expect_type({
    opensimplex2:::.doc_seed_text()
  }, "character")
})

test_that("Sampling 2d space requires identical length of coords", {
  expect_error({
    space <- opensimplex_space(dimensions = 2L)
    space$sample(1:10, 1:20)
  }, "should have same length")
})

test_that("Sampling 3d space requires identical length of coords", {
  expect_error({
    space <- opensimplex_space(dimensions = 3L)
    space$sample(1:10, 1:10, 1:20)
  }, "should have same length")
})

test_that("Sampling 4d space requires identical length of coords", {
  expect_error({
    space <- opensimplex_space(dimensions = 4L)
    space$sample(1:10, 1:10, 1:10, 1:20)
  }, "should have same length")
})
