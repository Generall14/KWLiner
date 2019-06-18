#ifndef RESFILE_HPP
#define RESFILE_HPP

#include <QString>
#include <exception>
#include <memory>
#include "QFile"
#include "QTextStream"
#include "set.hpp"

/**
 * Klasa parsuje i przechowuje wyniki wskazanego pliku.
 */
class ResFile
{
public:
    ResFile(QString name, uint light, uint comment, uint code);
    ResFile();

    void parseFile(QString fileAdr, const Set* set);

    QString Name() const;
    uint Total() const;
    uint Light() const;
    uint Comment() const;
    uint Code() const;

    QString toString() const;

    bool operator<(const ResFile &other);

protected:
    virtual std::unique_ptr<QTextStream> getTextStreamFromFile(QFile &file);

private:
    QString _name;
    uint _total;
    uint _light;
    uint _comment;
    uint _code;
};

#endif
