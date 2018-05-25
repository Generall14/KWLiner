#ifndef DYSKRYMINATORSM_HPP
#define DYSKRYMINATORSM_HPP

#include "set.hpp"
#include <exception>

class DyskryminatorSM
{
public:
    DyskryminatorSM(const Set* set) throw(std::runtime_error);

    void ResetState();

    void PushChar(QChar sgn) throw(std::runtime_error);
    void PushEndl() throw(std::runtime_error);

    bool wasComment;
    QString outBuff;

private:
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
    QString awaitingDoubleEnd;
    QString awaitingStringException;
};

#endif
