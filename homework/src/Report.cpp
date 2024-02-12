#include "../include/Report.h"

Report::Report(std::string author_name, std::shared_ptr<IMuseum> museum_name) {
  _author_name = author_name;
  _museum = museum_name;
};

std::vector<std::shared_ptr<IImage>> IReport::form() {
  std::vector<std::shared_ptr<IImage>> images = _museum.get()->getImages();
  std::vector<std::shared_ptr<IImage>> images_for_transfer;
  for (auto image : images)
    if (image.get()->getAuthorName() == _author_name &&
        !image.get()->getExhibited())
      images_for_transfer.push_back(image);
  return images_for_transfer;
}

