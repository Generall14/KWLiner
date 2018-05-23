#ifndef CORE_HPP
#define CORE_HPP

#include <QString>
#include <QStringList>
#include <QVector>
#include <exception>
#include "resFile.hpp"

class Core
{
public:
    Core(QString mode, QString root, QStringList excludes = QStringList());

    ResFile GetSum() throw(std::runtime_error);
    QVector<ResFile> GetFiles() throw(std::runtime_error);

private:
    QString _mode;
    QString _root;
    QStringList _excludes;
    bool done = false;

    ResFile _total;
    QVector<ResFile> _files;

    void calc() throw(std::runtime_error);
};

#endif
