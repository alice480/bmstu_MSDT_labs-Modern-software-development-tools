#include "headers/l3_DomainLayer.h"
#include <iostream>

Museum::Museum(std::string name) : _name(name) {}

Museum::Museum(std::string name, std::vector<Image> images)
    : _name(name), _images(images) {}

void Museum::addImage(const Image &image) {
  std::lock_guard<std::mutex> locker(_images_mutex);
  _images.push_back(image);
}

std::string Museum::getName() const noexcept {
    std::lock_guard<std::mutex> locker(_images_mutex);
    return _name;
}

std::vector<Image> Museum::getImages() const noexcept {
    std::lock_guard<std::mutex> locker(_images_mutex);
    return _images;
}

bool Museum::write(std::ostream& os) {
    writeString(os, _name);

    size_t number_of_images = _images.size();
    writeNumber(os, number_of_images);

    for(const Image & image : _images)
    {
        writeString(os, image.getAuthorName());
        writeString(os, image.getImageName());
        writeNumber(os, image.getYearOfCreation());
        writeNumber(os, image.getExhibited());
    }

    return os.good();
}

std::shared_ptr<ICollectable> ItemCollector::read(std::istream &is) {
  std::string museum_name = readString(is);
  size_t images_count = readNumber<size_t>(is);

  std::vector<Image> images;
  images.reserve(images_count);
  std::shared_ptr<ICollectable> p = std::make_shared<Museum>(museum_name, images);

  return p;
}

Museum &ItemCollector::getMuseumRef(size_t index) {
    Museum *museum = static_cast<Museum *>(getItem(index).get());
    assert(museum != nullptr);
    return *museum;
}