library(magick)
library(opensimplex2)

logo_mask <- image_read("data-raw/logo-mask.png")
w <- image_info(mask)$width
h <- image_info(mask)$height
circle_canvas <- image_blank(w, h)
circle_mask   <- image_draw(circle_canvas)
symbols(w/2, h/2, circles = 0.95*w/2,
        bg = "white", inches = FALSE, add = TRUE)
dev.off()

set.seed(3)
scale_factor <- 80
size         <- image_info(mask)$width
nframes      <- 100
space        <- opensimplex_space("S", 4L)
coords       <- expand.grid(z = seq_len(size), t = seq_len(size), frame = seq_len(nframes))
coords$x     <- 100*sin((2*pi*coords$frame - 1)/nframes)
coords$y     <- 100*cos((2*pi*coords$frame - 1)/nframes)
coords$value <- space$sample(.5*coords$x/scale_factor,
                             .5*coords$y/scale_factor,
                             coords$z/scale_factor,
                             coords$t/scale_factor)

for (i in seq_len(nframes - 1)) {
  frame_data <- subset(coords, frame == i)
  mat <- matrix(frame_data$value, size, size)
  noise_frame <-
    array(c(
      ifelse(mat < 0, 1, 0),
      ifelse(mat < 0, 1, 0x51/255),
      ifelse(mat < 0, 1, 0x72/255)
    ), dim = c(dim(mat), 3)) |>
    image_read()
  masked_frame <- image_composite(noise_frame, circle_mask,
                                  operator = "copyopacity")
  
  fn <- file.path(
    tempdir(),
    sprintf("logoframe%03i.png", i)
  )
  mosaic <-
    image_mosaic(
    c(
      masked_frame,
      logo_mask
    ) |>
      image_background("none")
  )
  if (i == 93) {
    image_write(mosaic, "data-raw/logo-first-frame.png")
  }
  mosaic |>
    image_resize("200", filter = "Lanczos") |>
    image_write(fn)
}

frames <- list.files(tempdir(),
                     pattern = "logoframe[0-9]{3}\\.png$",
                     full.names = TRUE)

gifski::gifski(
  frames, "man/figures/logo-anim.gif", width = "200", delay = .1
)

unlink(frames)
