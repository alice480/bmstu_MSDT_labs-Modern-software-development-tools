#ifndef _INCLUDE_IREPORT_H_
#define _INCLUDE_IREPORT_H_

#include <string>
#include <vector>

#include "Museum.h"

class IReport {
 public:
  virtual ~IReport() = default;
  virtual std::vector<std::shared_ptr<IImage>> form();

 protected:
  std::string _author_name;
  std::shared_ptr<IMuseum> _museum;
};

class Report : public IReport {
 public:
  Report(std::string author_name, std::shared_ptr<IMuseum> museum_name);
};

#endif  // _INCLUDE_IREPORT_H_
