#' Return a data frame of all possible Exif tags
#'
#' @md
#' @param filter_key a regular expression to filter key names by. If `NULL` then
#'        no key name filtering will be performed.
#' @param filter_type a vector of "ascii", "long", "short", "rational", "byte",
#'        "sshort", "srational", "float", "double", or "comment".
#'        if `NULL` then all types will be considered.
#' @return data frame
#' @export
exif_tags <- function(filter_key=NULL, filter_type=NULL) {

  if (is.null(filter_key)) filter_key <- ".*"

  if (!is.null(filter_type)) {
    filter_type <- unique(tolower(filter_type))
    filter_type <- match.arg(filter_type, .exiv_types, several.ok = TRUE)
  } else {
    filter_type <- .exiv_types
  }

  .exiv_keys[
    grepl(filter_key, .exiv_keys$key, ignore.case = TRUE) &
      (.exiv_keys$type %in% filter_type),
  ]

}