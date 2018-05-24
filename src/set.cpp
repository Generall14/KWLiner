#include "set.hpp"
#include "sets/setCpp.hpp"
#include "sets/setMSP.hpp"

Set::Set(QString name):
    _name(name)
{

}

QSharedPointer<Set> Set::GetSet(QString set) throw(std::runtime_error)
{
    if(!set.compare("C/C++"))
        return QSharedPointer<Set>(new SetCpp());
    else if(!set.compare("MSP430 asm"))
        return QSharedPointer<Set>(new SetMSP());
    else
        throw std::runtime_error(QString("Set::GetSet: Nie rozpoznano zestawu "+set).toStdString());
}

QStringList Set::GetSetsList()
{
    QStringList tmp = {"C/C++", "MSP430 asm"};
    return tmp;
}

QString Set::GetName() const
{
    return _name;
}

QStringList Set::GetSuffixes() const
{
    return _suffixes;
}

QStringList Set::GetOneLineComments() const
{
    return _oneLlineComm;
}

QVector<QPair<QString, QString> > Set::GetStartEndComments() const
{
    return _seComm;
}
