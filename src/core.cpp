#include "core.hpp"
#include "FileList.hpp"
#include "src/resFile.hpp"


/**
 * @param mode - tekstowe wskazanie zestawu Set.
 * @param root - adres do katalogu w którym rekurencyjnie mają być wyszukane pliki.
 * @param excludes - ignorowane pliki (pliki których adres zawiera jeden z tych tekstów zostaną zignorowane), porównanie
 * działa jako CaseInsensitive.
 */
Core::Core(QString mode, QString root, QStringList excludes):
    _mode(mode),
    _root(root),
    _excludes(excludes)
{

}

Core::Core():
    Core("", "")
{

}

void Core::Calc()
{
    _set = Set::GetSet(_mode);

    uint light = 0, comment = 0, code = 0;
    FileList fl(_root, _set->GetSuffixes(), _excludes);
    QStringList files = fl.GetFileList();
    emit progress(0, files.size());
    for(int i=0;i<files.size();++i)
    {
        ResFile temp;
        temp.parseFile(files.at(i), _set.data());
        _files.append(temp);
        light += _files.last().Light();
        comment += _files.last().Comment();
        code += _files.last().Code();
        emit progress(i+1, files.size());
    }

    _total = ResFile("SUMMED", light, comment, code);

    done = true;
}

ResFile Core::GetSum()
{
    if(!done)
        Calc();

    return _total;
}

QVector<ResFile> Core::GetFiles()
{
    if(!done)
        Calc();

    return _files;
}

QSharedPointer<Set> Core::GetSet()
{
    if(!done)
        Calc();

    return _set;
}
