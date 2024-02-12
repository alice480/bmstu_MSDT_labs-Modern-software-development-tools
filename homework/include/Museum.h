#ifndef _INCLUDE_IMUSEUM_H_
#define _INCLUDE_IMUSEUM_H_

#include <memory>
#include <random>
#include <string>
#include <vector>

#include "Image.h"

class IMuseum {
 public:
  virtual ~IMuseum() = default;

  virtual void addImage(std::shared_ptr<IImage> new_image);
  virtual std::vector<std::shared_ptr<IImage>> getImages() noexcept;

 protected:
  std::string _name;
  std::vector<std::shared_ptr<IImage>> _images;
};

class Museum : public IMuseum {
 public:
  Museum(std::string name);
};

#endif  // _INCLUDE_MUSEUM_H_