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

QSharedPointer<Set> Set::GetSet(QString set)
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

bool Set::isValid() const
{
    if(_name.isEmpty())
        return false;

    if(_suffixes.isEmpty())
        return false;
    for(auto str: _suffixes)
    {
        if(str.isEmpty())
            return false;
    }

    for(auto str: _oneLlineComm)
    {
        if(str.isEmpty())
            return false;
    }

    for(auto p: _seComm)
    {
        if( (p.first.isEmpty()) || (p.second.isEmpty()) )
            return false;
    }

    for(auto p: _striInd)
    {
        if(p.first.isEmpty())
            return false;
    }

    return true;
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
