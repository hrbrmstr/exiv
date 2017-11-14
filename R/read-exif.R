#' Retrieve Exif Data From An Image
#'
#' @md
#' @param x path to image file
#' @return data frame or `NULL` if no Exif data is present
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