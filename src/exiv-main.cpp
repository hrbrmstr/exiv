#include <Rcpp.h>
using namespace Rcpp;
#include <exiv2/exiv2.hpp>
#include <iostream>
#include <iomanip>
#include <cassert>

// [[Rcpp::export]]
List int_get_exif(std::string path) {

  CharacterVector key;
  CharacterVector val;

  try {

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);
    assert(image.get() != 0);
    image->readMetadata();
    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
      return(NULL);
      // std::string error("DOmEo-RX0AAX1rd.jpg");
      // error += ": No Exif data found in the file";
      // throw Exiv2::Error(1, error);
    }
    Exiv2::ExifData::const_iterator end = exifData.end();
    for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
      // const char* tn = i->typeName();
      key.push_back(i->key());
      val.push_back(i->value().toString());
      // std::cout << std::setw(44) << std::setfill(' ') << std::left
      //           << i->key() << " "
      //           << "0x" << std::setw(4) << std::setfill('0') << std::right
      //           << std::hex << i->tag() << " "
      //           << std::setw(9) << std::setfill(' ') << std::left
      //           << (tn ? tn : "Unknown") << " "
      //           << std::dec << std::setw(3)
      //           << std::setfill(' ') << std::right
      //           << i->count() << "  "
      //           << std::dec << i->value()
      //           << "\n";
    }
  }
  //catch (std::exception& e) {
  //catch (Exiv2::AnyError& e) {
  catch (Exiv2::Error& e) {
    // std::cout << "Caught Exiv2 exception '" << e.what() << "'\n";
  }

  return(
    List::create(
      _["exif_key"] = key,
      _["exif_val"] = val
    )
  );

}

// [[Rcpp::export]]
void int_set_exif_ascii(std::string path, std::string key, std::string value) {

  try {
    Exiv2::ExifData exifData;

    exifData[key] = value;
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);

    image.get();
    image->readMetadata();

    Exiv2::Value::AutoPtr ex_val = Exiv2::Value::create(Exiv2::asciiString);
    ex_val->read(value);

    image->exifData().add(Exiv2::ExifKey(key), ex_val.get());

    image->writeMetadata();

  } catch(Exiv2::AnyError& e) {
  }

}
