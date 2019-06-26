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

/**
 * Klasa wyszukuje pliki zgodne ze wzorcem oraz przetwarza je. Zwraca dane zsumowane oraz listę z danymi
 * dla poszczególnych plików.
 */
class Core : public QObject
{
    Q_OBJECT
public:
    Core(QString mode, QString root, QStringList excludes = QStringList());
    Core();

    ResFile GetSum();
    QVector<ResFile> GetFiles();
    QSharedPointer<Set> GetSet();
    void Calc();

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
