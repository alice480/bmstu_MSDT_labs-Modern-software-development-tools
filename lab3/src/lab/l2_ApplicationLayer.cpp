#include "headers/l2_ApplicationLayer.h"

#include <algorithm>

inline const std::string DATA_DEFAULT_NAME = "lab.data";

bool Application::performCommand(const std::vector<std::string> & args)
{
    if (args.empty())
        return false;

    // load [имя_файла]
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

    // save [имя_файла]
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

    // clean
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

    // add new museum
    // aM museum_name
    if (args[0] == "aM" || args[0] == "addMuseum")
    {
        if (args.size() != 2)
        {
            _out.Output("Некорректное количество аргументов команды addMuseum");
            return false;
        }

        _col.addItem(std::make_shared<Museum>(args[1].c_str()));
        return true;
    }

    // add new image to museum
    // museum_number author_name image_name year_of_creation exhibited
    if (args[0] == "aI" || args[0] == "addImage")
    {
        if (args.size() != 6)
        {
            _out.Output("Некорректное количество аргументов команды addImage");
            return false;
        }

        Museum & museum = _col.getMuseumRef(stoul(args[1]));
        std::vector<std::shared_ptr<Image>> v = museum.getImages();
        v.push_back(std::make_shared<Image>(args[2], args[3], std::stoi(args[4]), std::stoi(args[5])));
        museum.setImages(v);

        return true;
    }

    // remove museum_number
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

    // update museum_number name
    if (args[0] == "u" || args[0] == "update")
    {
        if (args.size() != 3)
        {
            _out.Output("Некорректное количество аргументов команды update");
            return false;
        }

        _col.updateItem(stoul(args[1]), std::make_shared<Museum>(args[2].c_str()));
        return true;
    }

    // view
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
            if (!_col.isRemoved(i))
            {
                const Museum & item = _col.getMuseumRef(i);

                _out.Output("[" + std::to_string(i) + "] "
                        + item.getName() + " ");

                for(auto image: item.getImages())
                    _out.Output("\t" + image.get()->getAuthorName() + ": " + 
                                        image.get()->getImageName() + ", " + 
                                        std::to_string(image.get()->getYearOfCreation()));

                count ++;
            }
        }

        _out.Output("Количество элементов в коллекции: " + std::to_string(count));
        return true;
    }

    // report museum_number author_name
    if (args[0] == "rp" || args[0] == "report")
    {
        if (args.size() != 3)
        {
            _out.Output("Некорректное количество аргументов команды report");
            return false;
        }
        
        int museum_number = std::stoi(args[1]);
        std::string author_name = args[2];

        const Museum & museum = _col.getMuseumRef(museum_number);

        
        std::vector<std::shared_ptr<Image>> images = museum.getImages();
        std::vector<std::shared_ptr<Image>> images_for_transfer;
        for (auto image : images)
            if (image.get()->getAuthorName() == author_name &&
                !image.get()->getExhibited())
            images_for_transfer.push_back(image);


        for (auto image: images_for_transfer)
            _out.Output(image.get()->getAuthorName() + " " +
                        image.get()->getImageName() + " " +
                        std::to_string(image.get()->getYearOfCreation()));
        
        return true;
    }

    _out.Output("Недопустимая команда '" + args[0] + "'");
    return false;
}
