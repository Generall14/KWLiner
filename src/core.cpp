#include "core.hpp"
#include "FileList.hpp"
#include <QDebug>

Core::Core(QString mode, QString root, QStringList excludes):
    _mode(mode),
    _root(root),
    _excludes(excludes)
{

}

void Core::calc() throw(std::runtime_error)
{
    // <TODO> soma calcs
    _set = Set::GetSet(_mode);

    FileList fl(_root, _set->GetSuffixes(), _excludes);
    for(auto str: fl.GetFileList())
        qDebug() << str;

    done = true;
}

ResFile Core::GetSum() throw(std::runtime_error)
{
    if(!done)
        calc();

    return _total;
}

QVector<ResFile> Core::GetFiles() throw(std::runtime_error)
{
    if(!done)
        calc();

    return _files;
}

QSharedPointer<Set> Core::GetSet() throw(std::runtime_error)
{
    if(!done)
        calc();

    return _set;
}
