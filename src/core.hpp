#ifndef CORE_HPP
#define CORE_HPP

#include <QString>
#include <QStringList>
#include <QVector>
#include <exception>
#include <QSharedPointer>
#include <src/set.hpp>
#include "resFile.hpp"

class Core
{
public:
    Core(QString mode, QString root, QStringList excludes = QStringList());
    Core();

    ResFile GetSum() throw(std::runtime_error);
    QVector<ResFile> GetFiles() throw(std::runtime_error);
    QSharedPointer<Set> GetSet() throw(std::runtime_error);

private:
    QString _mode;
    QString _root;
    QStringList _excludes;
    bool done = false;

    QSharedPointer<Set> _set;
    ResFile _total;
    QVector<ResFile> _files;

    void calc() throw(std::runtime_error);
};

#endif
