#include "../include/Image.h"

void IImage::setExhibited(bool value) { _exhibited = value; }

bool IImage::getExhibited() { return _exhibited; }

std::string IImage::getAuthorName() { return _author_name; }

std::string IImage::getName() { return _image_name; }

Image::Image(std::string author_name, std::string image_name) {
  _author_name = author_name;
  _image_name = image_name;
}
