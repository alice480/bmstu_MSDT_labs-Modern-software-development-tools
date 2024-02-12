#include "headers/l2_ApplicationLayer.h"

#include <algorithm>
#include <thread>

const int OUTPUT_LIMIT = 1000;

void Application::work()
{
  std::vector<std::string> args = split(_command);
  if (args.empty())
    return;

  // count
  if (args[0] == "c" || args[0] == "count")
  {
    if (args.size() != 1)
    {
      _out.Output("Некорректное количество аргументов команды count");
      return;
    }

    _out.Output(std::to_string(_col.getSize()));
    return;
  }

  // add new museum
  // aM/addMuseum [museum_name]
  if (args[0] == "aM" || args[0] == "addMuseum")
  {
    if (args.size() != 2)
    {
      _out.Output("Некорректное количество аргументов команды addMuseum");
      return;
    }

    _col.addItem(std::make_shared<Museum>(args[1].c_str()));
    return;
  }

  // add new image to museum
  // aI/addImage [museum_number] [author_name] [image_name] [year_of_creation] [exhibited]
  if (args[0] == "aI" || args[0] == "addImage") {
    if (args.size() != 6) {
      _out.Output("Некорректное количество аргументов команды addImage");
      return;
    }

    Museum &museum = _col.getMuseumRef(stoul(args[1]));

    museum.addImage(Image(args[2], args[3], std::stoi(args[4]),
                          std::stoi(args[5])));
    return;
  }

  // remove [museum_number]
  if (args[0] == "r" || args[0] == "remove")
  {
    if (args.size() != 2)
    {
      _out.Output("Некорректное количество аргументов команды remove");
      return;
    }

    _col.removeItem(stoul(args[1]));
    return;
  }

  // update [museum_number] [museum_name]
  if (args[0] == "u" || args[0] == "update")
  {
    if (args.size() != 3)
    {
      _out.Output("Некорректное количество аргументов команды update");
      return;
    }

    _col.updateItem(stoul(args[1]), std::make_shared<Museum>(args[2].c_str()));
    return;
  }

  // view [lines_limit] [images_limit]
  if (args[0] == "v" || args[0] == "view")
  {
    if (args.size() > 3)
    {
      _out.Output("Некорректное количество аргументов команды view");
      return;
    }

    size_t lines_limit = OUTPUT_LIMIT;
    if (args.size() > 1)
      lines_limit = stoul(args[1]);

    size_t visits_limit = OUTPUT_LIMIT;
    if (args.size() > 2)
      visits_limit = stoul(args[2]);

    size_t count = 0;
    for (size_t i = 1; i <= _col.getSize(); ++i)
    {
      if (!_col.isRemoved(i))
      {
        const Museum &item = _col.getMuseumRef(i);

        if (count < lines_limit)
        {
          _out.Output("[" + std::to_string(i) + "] " + item.getName() + " ");

          size_t images_count = 0;
          for (const Image &image : item.getImages())
          {
            if (images_count < visits_limit)
              _out.Output("\t" + image.getAuthorName() + ": " +
                          image.getImageName() + ", " +
                          std::to_string(image.getYearOfCreation()));

            images_count++;
          }

          if (images_count >= visits_limit)
            _out.Output("\t... " + std::to_string(images_count) + " визитов");
        }
        else if (count == lines_limit)
          _out.Output("Выведено первые " + std::to_string(lines_limit) + " строк");
        count++;
      }
    }

    _out.Output("Количество музеев в коллекции: " + std::to_string(count));
    return;
  }

  // report [museum_number] [author_name]
  if (args[0] == "rp" || args[0] == "report")
  {
    if (args.size() != 3)
    {
      _out.Output("Некорректное количество аргументов команды report");
      return;
    }

    int museum_number = std::stoi(args[1]);
    std::string author_name = args[2];

    const Museum &museum = _col.getMuseumRef(museum_number);

    std::vector<Image> images = museum.getImages();

    for (size_t i = 0; i < images.size(); i++) {
      if (!images[i].getExhibited() && images[i].getAuthorName() == author_name)
        _out.Output(images[i].getAuthorName() + ": " +
                  images[i].getImageName() + ", " +
                  std::to_string(images[i].getYearOfCreation()));
    }
    return;
  }

  _out.Output("Недопустимая команда '" + args[0] + "'");
  return;
}

std::vector<std::string> Application::split(const std::string &str) {
  std::vector<std::string> res;
  size_t start_pos = 0, end_pos = 0;

  while (end_pos < str.size()) {
    for (start_pos = end_pos; start_pos < str.size(); ++start_pos)
      if (str[start_pos] != ' ')
        break;

    if (start_pos == str.size())
      return res;

    for (end_pos = start_pos; end_pos < str.size(); ++end_pos)
      if (str[end_pos] == ' ')
        break;

    res.push_back(str.substr(start_pos, end_pos - start_pos));
  }

  return res;
}
