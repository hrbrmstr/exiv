# Build against exiv2 static libs
VERSION <- commandArgs(TRUE)
if(!file.exists(sprintf("../windows/exiv2-%s/include/exiv2/exiv2.hpp", VERSION))){
  if(getRversion() < "3.3.0") setInternet2()
  download.file(sprintf("https://github.com/rwinlib/exiv2/archive/v%s.zip", VERSION), "lib.zip", quiet = TRUE)
  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")
}
