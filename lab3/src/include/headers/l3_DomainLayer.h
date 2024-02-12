#ifndef _INCLUDE_DOMAIN_LAYER_H
#define _INCLUDE_DOMAIN_LAYER_H

#include "l4_InfrastructureLayer.h"
#include <iostream>

const size_t MAX_NAMES_LENGTH = 200;
const size_t MIN_YEAR_OF_CREATION = 1;
const size_t MAX_YEAR_OF_CREATION = 2023;

class Image {
  std::string _author_name;
  std::string _image_name;
  uint16_t _year_of_creation;
  bool _exhibited = 0;

protected:
  bool invariant() const;

public:
  Image() = delete;
  Image(const Image &p) = delete;

  Image &operator=(const Image &p) = delete;

  Image(const std::string & author_name, const std::string & image_name, uint16_t year_of_creation, bool exhibited);

  const std::string &getAuthorName() const;
  const std::string &getImageName() const;
  bool getExhibited();
  uint16_t getYearOfCreation() const;

  void setExhibited(bool value);
};


class Museum : public ICollectable {
  std::string _name;
  std::vector<std::shared_ptr<Image>> _images;

public:
  Museum() = delete;
  Museum(std::string name);
  Museum(std::string name, std::vector<std::shared_ptr<Image>> images);
  ~Museum() = default;
  // adding Images
  void setImages(const std::vector<std::shared_ptr<Image>> &images);
  // getters
  std::vector<std::shared_ptr<Image>> getImages() const noexcept;
  std::string getName() const noexcept;

  virtual bool write(std::ostream &os) override;
};

class ItemCollector : public ACollector {
public:
  virtual std::shared_ptr<ICollectable> read(std::istream &is) override;
  Museum & getMuseumRef(size_t index);
};

#endif // _INCLUDE_DOMAIN_LAYER_H
