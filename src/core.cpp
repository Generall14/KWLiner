#include "core.hpp"
#include "FileList.hpp"
#include "src/resFile.hpp"
#include <QDebug>

Core::Core(QString mode, QString root, QStringList excludes):
    _mode(mode),
    _root(root),
    _excludes(excludes)
{

}

void Core::calc() throw(std::runtime_error)
{
    _set = Set::GetSet(_mode);

    uint light = 0, comment = 0, code = 0;
    FileList fl(_root, _set->GetSuffixes(), _excludes);
    for(auto str: fl.GetFileList())
    {
        _files.append(ResFile::ParseFile(str));
        light += _files.last().Light();
        comment += _files.last().Comment();
        code += _files.last().Code();
        qDebug() << _files.last().toString();
    }

    _total = ResFile("SUMMED", light, comment, code);

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
