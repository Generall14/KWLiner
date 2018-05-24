#ifndef GLOBALXMLFILE_HPP
#define GLOBALXMLFILE_HPP

#include "pugixml.hpp"

class GlobalXmlFile
{
public:
    ~GlobalXmlFile();
    static pugi::xml_node getMainNode();

private:
    GlobalXmlFile();

    pugi::xml_document file;
};

#endif
