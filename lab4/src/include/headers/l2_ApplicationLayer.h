#ifndef _INCLUDE_APPLICATION_LAYER_H
#define _INCLUDE_APPLICATION_LAYER_H

#include <string>

#include "l3_DomainLayer.h"
#include "tp/Task_interface.h"

class IOutput {
public:
  virtual ~IOutput() = default;

  virtual void Output(std::string s) const = 0;
};

class Application : public tp::Task_interface {
  ItemCollector &_col;
  std::string _command;
  const IOutput &_out;

  std::vector<std::string> split(const std::string &str);

public:
  Application() = delete;
  Application(const Application &) = delete;

  Application &operator=(const Application &) = delete;

  Application(ItemCollector &col, const std::string &command,
              const IOutput &out)
      : _col(col), _command(command), _out(out) {}

  virtual void work() override;
};

#endif // _INCLUDE_APPLICATION_LAYER_H
