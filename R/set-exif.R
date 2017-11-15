#' Set Exif tag data on an image file
#'
#' CURRENTLY ONLY HANDLES ASCII
#'
#' @md
#' @param x path to image file
#' @param tag Exif tag name to set (full `Title.Case.Dotted` name)
#' @param val Exif tag value; `rational` should be a two element numeric vector
#' @return data frame of image Exif values
#' @export
set_exif <- function(x, tag, val) {

  x <- path.expand(x)

  if (file.exists(x)) {

    target_tag <- .exiv_keys[(tag == .exiv_keys$key) | (tag == .exiv_keys$rname),]

    if (nrow(target_tag) != 1) stop("Tag not found")

    if (!(target_tag$type %in% c("ascii", "comment", "short", "long", "rational", "srational"))) {
      stop("Tags with ascii, comment, short, long, or [u]rational values only currently supported")
    }

    if (target_tag$type == "ascii") int_set_exif_ascii(x, tag, val)
    if (target_tag$type == "comment") int_set_exif_ascii(x, tag, val)

    if (target_tag$type == "long") int_set_exif_long(x, tag, as.integer(val))
    if (target_tag$type == "short") int_set_exif_short(x, tag, as.integer(val))

    if (target_tag$type == "srational") {
      if (length(val) != 2) stop("Numerator and denominator for rational values")
      int_set_exif_rational(x, tag, as.integer(val[1]), as.integer(val[2]))
    }

    if (target_tag$type == "rational") {
      if (length(val) != 2) stop("Numerator and denominator for unsigned rational values")
      int_set_exif_urational(x, tag, as.integer(val[1]), as.integer(val[2]))
    }

    # if (target_tag$type == "float") int_set_exif_float(x, tag, as.numeric(val))
    # if (target_tag$type == "double") int_set_exif_dobule(x, tag, as.double(val))

    read_exif(x)

  } else {
    stop("File not found")
  }

}

# .exiv_types <-
#   c("ascii", "long", "short", "rational", "byte", "sshort",
#     "srational", "float", "double", "comment")