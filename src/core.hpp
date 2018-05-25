#ifndef CORE_HPP
#define CORE_HPP

#include <QString>
#include <QStringList>
#include <QVector>
#include <exception>
#include <QSharedPointer>
#include <src/set.hpp>
#include <QObject>
#include "resFile.hpp"

class Core : public QObject
{
    Q_OBJECT
public:
    Core(QString mode, QString root, QStringList excludes = QStringList());
    Core();

    ResFile GetSum() throw(std::runtime_error);
    QVector<ResFile> GetFiles() throw(std::runtime_error);
    QSharedPointer<Set> GetSet() throw(std::runtime_error);
    void Calc() throw(std::runtime_error);

signals:
    void progress(int current, int total);

private:
    QString _mode;
    QString _root;
    QStringList _excludes;
    bool done = false;

    QSharedPointer<Set> _set;
    ResFile _total;
    QVector<ResFile> _files;
};

#endif
