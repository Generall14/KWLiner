#include "set.hpp"
#include "sets/setCpp.hpp"
#include "sets/setMSP.hpp"
#include "sets/setPIC.hpp"
#include "sets/setJava.hpp"
#include "sets/setPython.hpp"

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
    else if(!set.compare("PIC asm"))
        return QSharedPointer<Set>(new SetPIC());
    else if(!set.compare("Python"))
        return QSharedPointer<Set>(new SetPython());
    else if(!set.compare("Java"))
        return QSharedPointer<Set>(new SetJava());
    else
        throw std::runtime_error(QString("Set::GetSet: Nie rozpoznano zestawu "+set).toStdString());
}

QStringList Set::GetSetsList()
{
    QStringList tmp = {"C/C++", "MSP430 asm", "PIC asm", "Python", "Java"};
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

QVector<QPair<QString, QString> > Set::GetStringInd() const
{
    return _striInd;
}
