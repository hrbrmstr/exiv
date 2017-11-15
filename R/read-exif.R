#' Retrieve Exif data from an image file
#'
#' FEEDBACK WELCOME/ENCOURAGED FOR WHAT THIS SHOULD RETURN
#'
#' @md
#' @param x path to image file
#' @return data frame or `NULL` if no Exif data is present. This does mean that all the
#'         values are conv are `toString()`-ified on the C++ side. This could easily return
#'         a named list of real values. Not sure how to handle it, but there are also
#'         other pkgs for handing this.
#' @export
read_exif <- function(x) {

  x <- path.expand(x)
  if (file.exists(x)) {
    y <- cbind.data.frame(int_get_exif(x), stringsAsFactors=FALSE)
    class(y) <- c("tbl_df", "tbl", "data.frame")
    y
  } else {
    stop("File not found")
  }

}