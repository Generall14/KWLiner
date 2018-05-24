#ifndef RESTORABLE_HPP
#define RESTORABLE_HPP

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QStringList>
#include "GlobalXmlFile.hpp"
#include "pugixml.hpp"

class Restorable
{
public:
    Restorable(QString className);

protected:
    template<typename T> void Store(QString name, T value)
    {
        pugi::xml_node node = GlobalXmlFile::getMainNode().child(_className.toStdString().c_str());
        if(node.empty())
            node = GlobalXmlFile::getMainNode().append_child(_className.toStdString().c_str());
        node.remove_attribute(name.toStdString().c_str());
        node.append_attribute(name.toStdString().c_str()) = value;
    }
    void Store(QString name, QString value);
    void Store(QString name, QByteArray value);
    void Store(QString name, QStringList list);

    int RestoreAsInt(QString name, int onFail);
    unsigned int RestoreAsInt(QString name, unsigned int onFail);
    float RestoreAsFloat(QString name, float onFail);
    bool RestoreAsBool(QString name, bool onFail);
    QString RestoreAsString(QString name, QString onFail);
    QByteArray RestoreAsByteArray(QString name, QByteArray onFail);
    QStringList RestoreAsQStringList(QString name, QStringList onFail);

private:
    QString _className;
};

#endif
