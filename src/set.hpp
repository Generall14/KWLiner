#ifndef SET_HPP
#define SET_HPP

#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QPair>
#include <QVector>
#include <exception>

/**
 * Klasa opisuje znaczniki tekstowe dla danego typu kodu.
 */
class Set
{
public:
    static QSharedPointer<Set> GetSet(QString set);
    static QStringList GetSetsList();

    QString GetName() const;
    QStringList GetSuffixes() const;
    QStringList GetOneLineComments() const;
    QVector<QPair<QString, QString> > GetStartEndComments() const;
    QVector<QPair<QString, QString> > GetStringInd() const;

    bool isValid() const;

protected:
    Set(QString name);

    QString _name;
    QStringList _suffixes; /**<Rozszerzenia plików związanych z zestawem.*/
    QStringList _oneLlineComm; /**<Znaczniki rozpoczęcia komentarza jednej linii.*/
    QVector<QPair<QString, QString> > _seComm; /**<Sparowane znaczniki początku i końca komentarza ciągłego.*/
    QVector<QPair<QString, QString> > _striInd; /**<Pary znacznika stringu oraz wewnętrznego ignorowania tego znacznika.*/
};

#endif
