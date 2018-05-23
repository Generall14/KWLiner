#include "core.hpp"

Core::Core(QString mode, QString root, QStringList excludes):
    _mode(mode),
    _root(root),
    _excludes(excludes)
{

}

void Core::calc() throw(std::runtime_error)
{
    // <TODO> soma calcs
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
