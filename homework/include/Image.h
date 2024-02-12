#ifndef _INCLUDE_IIMAGE_H_
#define _INCLUDE_IIMAGE_H_

#include <string>

class IImage {
 public:
  virtual ~IImage() = default;
  virtual void setExhibited(bool value);
  virtual bool getExhibited();
  virtual std::string getAuthorName();
  virtual std::string getName();

 protected:
  std::string _author_name;
  std::string _image_name;
  bool _exhibited = 0;
};

class Image : public IImage {
 public:
  Image(std::string author_name, std::string image_name);
};

#endif  // _INCLUDE_IIMAGE_H_