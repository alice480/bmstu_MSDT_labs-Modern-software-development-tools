#include "../include/Museum.h"

void IMuseum::addImage(std::shared_ptr<IImage> new_image) {
  // determines whether the image is being exhibited
  new_image.get()->setExhibited(std::rand() % 2);
  // adds images to the vector
  _images.push_back(new_image);
}

std::vector<std::shared_ptr<IImage>> IMuseum::getImages() noexcept {
  return _images;
}

Museum::Museum(std::string name) { _name = name; }
