#include <Rcpp.h>

#include <exiv2/exiv2.hpp>

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace Rcpp;

// [[Rcpp::export]]
List int_get_exif(std::string path) {

  CharacterVector key;
  CharacterVector val;
  CharacterVector type_name;

  try {

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);

    image.get();
    image->readMetadata();

    Exiv2::ExifData &exifData = image->exifData();

    if (exifData.empty()) return(R_NilValue);

    Exiv2::ExifData::const_iterator end = exifData.end();

    for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
      key.push_back(i->key());
      val.push_back(i->value().toString());
      type_name.push_back(i->typeName());
    }

  } catch (Exiv2::Error& e) {
  }

  return(
    List::create(
      _["exif_key"] = key,
      _["exif_val"] = val,
      _["exif_type"] = type_name
    )
  );

}

// [[Rcpp::export]]
void int_set_exif_ascii(std::string path, std::string key, std::string value) {

  try {

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);

    image.get();
    image->readMetadata();

    image->exifData()[key] = value;
//
//     Exiv2::Value::AutoPtr ex_val = Exiv2::Value::create(Exiv2::asciiString);
//     ex_val->read(value);
//
//     image->exifData().add(Exiv2::ExifKey(key), ex_val.get());

    image->writeMetadata();

  } catch(Exiv2::AnyError& e) {
  }

}

// [[Rcpp::export]]
void int_set_exif_long(std::string path, std::string key, long int value) {

  try {

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);

    image.get();
    image->readMetadata();

    image->exifData()[key] = (int32_t)value;

    image->writeMetadata();

  } catch(Exiv2::AnyError& e) {
  }

}

// [[Rcpp::export]]
void int_set_exif_short(std::string path, std::string key, long int value) {

  try {

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);

    image.get();
    image->readMetadata();

    image->exifData()[key] = (uint16_t)value;

    image->writeMetadata();

  } catch(Exiv2::AnyError& e) {
  }

}

// [[Rcpp::export]]
void int_set_exif_rational(std::string path, std::string key,
                           int32_t p, int32_t q) {

  try {

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);

    image.get();
    image->readMetadata();

    image->exifData()[key] = Exiv2::Rational(p, q);

    image->writeMetadata();

  } catch(Exiv2::AnyError& e) {
  }

}

// [[Rcpp::export]]
void int_set_exif_urational(std::string path, std::string key,
                            uint32_t p, uint32_t q) {

  try {

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);

    image.get();
    image->readMetadata();

    image->exifData()[key] = Exiv2::URational(p, q);

    image->writeMetadata();

  } catch(Exiv2::AnyError& e) {
  }

}
