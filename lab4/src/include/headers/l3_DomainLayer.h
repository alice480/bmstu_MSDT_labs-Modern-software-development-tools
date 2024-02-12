#ifndef _INCLUDE_DOMAIN_LAYER_H
#define _INCLUDE_DOMAIN_LAYER_H

#include "l4_InfrastructureLayer.h"

const size_t MAX_NAMES_LENGTH = 150;
const int MIN_YEAR_OF_CREATION = 1;
const int MAX_YEAR_OF_CREATION = 2024;

class Image {
  std::string _author_name;
  std::string _image_name;
  int _year_of_creation;
  bool _exhibited = 0;

public:
  Image() = delete;

  Image(const std::string &author_name, const std::string &image_name,
            int year_of_creation, bool exhibited):
             _author_name(author_name), _image_name(image_name),
      _year_of_creation(year_of_creation), _exhibited(exhibited) {}


  const std::string &getAuthorName() const { return _author_name; }
  const std::string &getImageName() const { return _image_name; }
  bool getExhibited() const {return _exhibited; }
  int getYearOfCreation() const { return _year_of_creation; }

  void setExhibited(bool value);
};

class Museum : public ICollectable {
  std::string _name;
  std::vector<Image> _images;
  mutable std::mutex _images_mutex;

protected:
    bool invariant() const;

public:
  Museum() = delete;
  Museum(std::string name);
  Museum(std::string name, std::vector<Image> images);
  ~Museum() = default;
  // adding Images
  void addImage(const Image &image);
  // getters
  std::vector<Image> getImages() const noexcept;
  std::string getName() const noexcept;

  virtual bool   write(std::ostream& os) override;
};

class ItemCollector : public ACollector {
public:
  virtual std::shared_ptr<ICollectable> read(std::istream &is) override;
  Museum &getMuseumRef(size_t index);
};

#endif // _INCLUDE_DOMAIN_LAYER_H
