#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/l2_ApplicationLayer.h"

class TerminalOutput : public IOutput {
 public:
  virtual void Output(std::string s) const override final;
};

void TerminalOutput::Output(std::string s) const { std::cout << s << std::endl; }

int main(int, char **) {

  std::cout << "Инструкция" << std::endl;
  std::cout << "l/load filename" << std::endl;
  std::cout << "s/save filename" << std::endl;
  std::cout << "c/clean" << std::endl;
  std::cout << "aM/addMuseum museum_name" << std::endl;
  std::cout << "aI/addImage museum_number author_name image_name year_of_creation exhibited" << std::endl;
  std::cout << "r/remove index" << std::endl;
  std::cout << "u/update museum_number museum_name" << std::endl;
  std::cout << "v/view" << std::endl;
  std::cout << std::endl;

  TerminalOutput out;
  Application app(out);

  for (std::string line; getline(std::cin, line);) {
    if (line.empty()) break;

    std::istringstream iss(line);
    std::vector<std::string> args;

    for (std::string str; iss.good();) {
      iss >> str;
      args.emplace_back(str);
    }

    if (!app.performCommand(args)) return 1;
  }

  std::cout << "Выполнение завершено успешно" << std::endl;
  return 0;
}
