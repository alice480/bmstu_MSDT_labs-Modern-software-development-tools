#include "../include/l3_DomainLayer.h"

bool Image::invariant() const {
    return _year_of_creation >= MIN_YEAR_OF_CREATION
        && _year_of_creation <= MAX_YEAR_OF_CREATION
        && !_author_name.empty() && _author_name.size() <= MAX_NAMES_LENGTH
        && !_image_name.empty() && _image_name.size() <= MAX_NAMES_LENGTH;
}

Image::Image(const std::string & author_name, const std::string & image_name, uint16_t year_of_creation, bool exhibited)
    : _author_name(author_name), _image_name(image_name), _year_of_creation(year_of_creation), _exhibited(exhibited) {
    assert(invariant());
}

const std::string & Image::getAuthorName() const { return _author_name; }

const std::string & Image::getImageName() const { return _image_name; }

uint16_t Image::getYearOfCreation() const {
    return _year_of_creation;
}

bool Image::getExhibited() { return _exhibited; }


Museum::Museum(std::string name) : _name(name) {}
Museum::Museum(std::string name, std::vector<std::shared_ptr<Image>> images) : _name(name), _images(images) {}

bool   Museum::write(std::ostream& os) {
    writeString(os, _name);

    size_t images_count = _images.size();
    writeNumber(os, images_count);
    
    for (auto image: _images) {
        writeString(os, image.get()->getAuthorName());
        writeString(os, image.get()->getImageName());
        writeNumber(os, image.get()->getYearOfCreation());
        writeNumber(os, image.get()->getExhibited());
    }

    return os.good();
}

void Museum::setImages(const std::vector<std::shared_ptr<Image>> &images) {
    _images = images;
}

std::string Museum::getName() const noexcept {
    return _name;
}

std::vector<std::shared_ptr<Image>> Museum::getImages() const noexcept {
  return _images;
}

std::shared_ptr<ICollectable> ItemCollector::read(std::istream& is) {
    std::string museum_name = readString(is, MAX_NAMES_LENGTH);
    size_t images_count = readNumber<size_t>(is);

    std::vector<std::shared_ptr<Image>> v;

    v.reserve(images_count);
    for(size_t i=0; i < images_count; ++i)
    {
        std::string author_name = readString(is, MAX_NAMES_LENGTH);
        std::string image_name = readString(is, MAX_NAMES_LENGTH);
        uint16_t year_of_creation = readNumber<uint16_t>(is);
        bool exhibited = readNumber<bool>(is);
        v.push_back(std::make_shared<Image>(author_name, image_name, year_of_creation, exhibited));
    }

    std::shared_ptr<ICollectable> p = std::make_shared<Museum>(museum_name, v);

    return p;
}

Museum &ItemCollector::getMuseumRef(size_t index)
{
    Museum & museum = *static_cast<Museum*>(getItem(index).get());

    return museum;
}