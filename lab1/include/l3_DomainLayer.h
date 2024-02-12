#ifndef _INCLUDE_DOMAIN_LAYER_H
#define _INCLUDE_DOMAIN_LAYER_H

#include "l4_InfrastructureLayer.h"

const size_t MAX_NAMES_LENGTH    = 50;
const size_t MIN_YEAR_OF_CREATION  = 1;
const size_t MAX_YEAR_OF_CREATION  = 2023;

class Image : public ICollectable {
    std::string _author_name;
    std::string _image_name;
    uint16_t    _year_of_creation;

protected:
    bool invariant() const;

public:
    Image() = delete;
    Image(const Image & p) = delete;

    Image & operator = (const Image & p) = delete;

    Image(const std::string & first_name, const std::string & last_name, uint16_t year_of_birth);

    const std::string & getAuthorName() const;
    const std::string & getImageName() const;
    uint16_t       getYearOfCreation() const;

    virtual bool   write(std::ostream& os) override;
};


class ItemCollector: public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream& is) override;
};

#endif // _INCLUDE_DOMAIN_LAYER_H
