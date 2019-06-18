#include "resFile.hpp"
#include "QFile"
#include "QTextStream"
#include <algorithm>
#include "dyskryminatorSM.hpp"

ResFile::ResFile(QString name, uint light, uint comment, uint code):
    _name(name),
    _total(light+comment+code),
    _light(light),
    _comment(comment),
    _code(code)
{

}

ResFile::ResFile():
    ResFile("", 0, 0, 0)
{

}

ResFile ResFile::ParseFile(QString fileAdr, const Set *set) throw(std::runtime_error)
{
    if(set == nullptr)
        throw std::runtime_error("ResFile::ParseFile: pusty wskaźnik na Set ");
    if(!set->isValid())
        throw std::runtime_error("ResFile::ParseFile: przekazany nieprawidłowy obiekt Set ");

    QFile file(fileAdr);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error(QString("ResFile::ParseFile: nie można otworzyć pliku "+fileAdr).toStdString());

    QString name = file.fileName().split("/").last();
    uint code = 0, light = 0, comment = 0;

    QTextStream ts(&file);
    DyskryminatorSM dys(set);

    while(!ts.atEnd())
    {
        QString line = ts.readLine();
        bool someComment = dys.DyscriminateLine(line);

        if(std::all_of(line.begin(), line.end(), [](QChar& c){return isspace(c.toLatin1());}))
        {
            if(someComment)
                comment++;
            else
                light++;
        }
        else
            code++;
    }

    file.close();
    return ResFile(name, light, comment, code);
}

QString ResFile::Name() const
{
    return _name;
}

uint ResFile::Total() const
{
    return _total;
}

uint ResFile::Light() const
{
    return _light;
}

uint ResFile::Comment() const
{
    return _comment;
}

uint ResFile::Code() const
{
    return _code;
}

QString ResFile::toString() const
{
    QString temp = _name+", ";
    temp.append(" total: " + QString::number(_total));
    temp.append(" code: " + QString::number(_code));
    temp.append(" comment: " + QString::number(_comment));
    temp.append(" light: " + QString::number(_light));
    return temp;
}

bool ResFile::operator<(const ResFile &other)
{
    if(_total>other.Total())
        return true;
    return false;
}
