#include "../include/l2_ApplicationLayer.h"

inline const std::string DATA_DEFAULT_NAME = "lab.data";

bool Application::performCommand(const std::vector<std::string> & args)
{
    if (args.empty())
        return false;

    if (args[0] == "l" || args[0] == "load")
    {
        std::string filename = (args.size() == 1) ? DATA_DEFAULT_NAME : args[1];

        if (!_col.loadCollection(filename))
        {
            _out.Output("Ошибка при загрузке файла '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "s" || args[0] == "save")
    {
        std::string filename = (args.size() == 1) ? DATA_DEFAULT_NAME : args[1];

        if (!_col.saveCollection(filename))
        {
            _out.Output("Ошибка при сохранении файла '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "c" || args[0] == "clean")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды clean");
            return false;
        }

        _col.clean();

        return true;
    }

    if (args[0] == "a" || args[0] == "add")
    {
        if (args.size() != 4)
        {
            _out.Output("Некорректное количество аргументов команды add");
            return false;
        }

        _col.addItem(std::make_shared<Image>(args[1].c_str(), args[2].c_str(), stoul(args[3])));
        return true;
    }

    if (args[0] == "r" || args[0] == "remove")
    {
        if (args.size() != 2)
        {
            _out.Output("Некорректное количество аргументов команды remove");
            return false;
        }

        _col.removeItem(stoul(args[1]));
        return true;
    }

    if (args[0] == "u" || args[0] == "update")
    {
        if (args.size() != 5)
        {
            _out.Output("Некорректное количество аргументов команды update");
            return false;
        }

        _col.updateItem(stoul(args[1]), std::make_shared<Image>(args[2].c_str(), args[3].c_str(), stoul(args[4])));
        return true;
    }

    if (args[0] == "v" || args[0] == "view")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды view");
            return false;
        }

        size_t count = 0;
        for(size_t i=0; i < _col.getSize(); ++i)
        {
            const Image & item = static_cast<Image &>(*_col.getItem(i));

            if (!_col.isRemoved(i))
            {
                _out.Output("[" + std::to_string(i) + "] "
                        + item.getAuthorName() + " "
                        + item.getImageName() + " "
                        + std::to_string(item.getYearOfCreation()));
                count ++;
            }
        }

        _out.Output("Количество элементов в коллекции: " + std::to_string(count));
        return true;
    }

    _out.Output("Недопустимая команда '" + args[0] + "'");
    return false;
}
