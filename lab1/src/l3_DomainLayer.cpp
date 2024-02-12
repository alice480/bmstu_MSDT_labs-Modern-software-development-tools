#include "../include/l3_DomainLayer.h"

bool Image::invariant() const {
    return _year_of_creation >= MIN_YEAR_OF_CREATION
        && _year_of_creation <= MAX_YEAR_OF_CREATION
        && !_author_name.empty() && _author_name.size() <= MAX_NAMES_LENGTH
        && !_image_name.empty() && _image_name.size() <= MAX_NAMES_LENGTH;
}

Image::Image(const std::string & author_name, const std::string & image_name, uint16_t year_of_creation)
    : _author_name(author_name), _image_name(image_name), _year_of_creation(year_of_creation) {
    assert(invariant());
}

const std::string & Image::getAuthorName() const { return _author_name; }

const std::string & Image::getImageName() const { return _image_name; }

uint16_t Image::getYearOfCreation() const {
    return _year_of_creation;
}

bool   Image::write(std::ostream& os) {
    writeString(os, _author_name);
    writeString(os, _image_name);
    writeNumber(os, _year_of_creation);

    return os.good();
}



std::shared_ptr<ICollectable> ItemCollector::read(std::istream& is) {
    std::string   author_name = readString(is, MAX_NAMES_LENGTH);
    std::string   image_name  = readString(is, MAX_NAMES_LENGTH);
    uint16_t year       = readNumber<uint16_t>(is);

    return std::make_shared<Image>(author_name, image_name, year);
}
