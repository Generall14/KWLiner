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
    DyskryminatorSM(const Set* set) throw(std::runtime_error);

    void ResetState();
    bool DyscriminateLine(QString &line);

private:
    void PushChar(QChar sgn) throw(std::runtime_error);
    QString PushEndl() throw(std::runtime_error);
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
