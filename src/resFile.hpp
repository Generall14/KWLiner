#ifndef RESFILE_HPP
#define RESFILE_HPP

#include <QString>
#include <exception>

class ResFile
{
public:
    ResFile(QString name, uint light, uint comment, uint code);
    ResFile();

    static ResFile ParseFile(QString fileAdr) throw(std::runtime_error);

    QString Name() const;
    uint Total() const;
    uint Light() const;
    uint Comment() const;
    uint Code() const;

    QString toString() const;

private:
    QString _name;
    uint _total;
    uint _light;
    uint _comment;
    uint _code;
};

#endif
