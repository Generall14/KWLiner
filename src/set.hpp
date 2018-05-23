#ifndef SET_HPP
#define SET_HPP

#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QPair>
#include <QVector>
#include <exception>

class Set
{
public:
    static QSharedPointer<Set> GetSet(QString set) throw(std::runtime_error);
    static QStringList GetSetsList();

    QString GetName() const;
    QStringList GetSuffixes() const;
    QStringList GetOneLineComments() const;
    QVector<QPair<QString, QString> > GetStartEndComments() const;

protected:
    Set(QString name);

    QString _name;
    QStringList _suffixes;
    QStringList _oneLlineComm;
    QVector<QPair<QString, QString> > _seComm;
};

#endif
