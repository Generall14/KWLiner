#ifndef DYSKRYMINATORSM_HPP
#define DYSKRYMINATORSM_HPP

#include "set.hpp"
#include <exception>

/**
 * Maszyna stanu usuwająca komentarze (według danych przekazanych jako Set) z podanych ciągów tekstowych.
 */
class DyskryminatorSM
{
public:
    DyskryminatorSM(const Set* set);

    void ResetState();
    bool DyscriminateLine(QString &line);

private:
    void PushChar(QChar sgn);
    QString PushEndl();
    bool wasComment;

    QStringList oneLineComments;
    QVector<QPair<QString, QString> > startEndComments;
    QVector<QPair<QString, QString> > stringInd;

    enum state
    {
        stateNormal,
        stateOneLineComment,
        statePermComment,
        stateString
    };

    state currentState;
    QString workBuff;
    QString outBuff;
    QString awaitingDoubleEnd;
    QString awaitingStringException;
};

#endif
