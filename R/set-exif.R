#' Set Exif tag data on an image file
#'
#' CURRENTLY ONLY HANDLES ASCII
#'
#' @md
#' @param x path to image file
#' @param tag Exif tag name to set (full `Title.Case.Dotted` name)
#' @param val Exif tag value
#' @return data frame of image Exif values
#' @export
set_exif <- function(x, tag, val) {

  x <- path.expand(x)
  if (file.exists(x)) {

    target_tag <- .exiv_keys[(tag == .exiv_keys$key) | (tag == .exiv_keys$rname),]
    if (nrow(target_tag) != 1) stop("Tag not found")

    if (!(target_tag$type == "ascii")) stop("Tags with ascii values only currently supported")

    if (target_tag$type == "ascii") int_set_exif_ascii(x, tag, val)

    read_exif(x)

  } else {
    stop("File not found")
  }

}

# .exiv_types <-
#   c("ascii", "long", "short", "rational", "byte", "sshort",
#     "srational", "float", "double", "comment")