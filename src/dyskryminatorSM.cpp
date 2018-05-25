#include "dyskryminatorSM.hpp"
#include <QString>

DyskryminatorSM::DyskryminatorSM(const Set* set) throw(std::runtime_error)
{
    if(set==nullptr)
        throw std::runtime_error("DyskryminatorSM::DyskryminatorSM: nullptr as argument");

    oneLineComments = set->GetOneLineComments();
    startEndComments = set->GetStartEndComments();
    stringInd = set->GetStringInd();

    ResetState();
}

void DyskryminatorSM::ResetState()
{
    currentState = stateNormal;
    wasComment = false;
    outBuff.clear();
    workBuff.clear();
    awaitingDoubleEnd.clear();
    awaitingStringException.clear();
}

void DyskryminatorSM::PushChar(QChar sgn) throw(std::runtime_error)
{
    int idx;
    switch (currentState)
    {
    //================== NORMAL =====================================================
    case stateNormal:
        outBuff.append(sgn);
        for(QString ol: oneLineComments)
        {
            if(ol.isEmpty())
                throw std::runtime_error("DyskryminatorSM::PushChar(QChar sgn): empty elemet in oneLineComments");
            idx = outBuff.indexOf(ol);
            if(idx>-1)
            {
                wasComment = true;
                outBuff = outBuff.remove(idx, ol.size());
                currentState = stateOneLineComment;
                return;
            }
        }
        for(QPair<QString, QString> pair: startEndComments)
        {
            if(pair.first.isEmpty())
                throw std::runtime_error("DyskryminatorSM::PushChar(QChar sgn): empty elemet in startEndComments.first");
            idx = outBuff.indexOf(pair.first);
            if(idx>-1)
            {
                wasComment = true;
                outBuff = outBuff.remove(idx, pair.first.size());
                workBuff.clear();
                awaitingDoubleEnd = pair.second;
                currentState = statePermComment;
                return;
            }
        }
        for(QPair<QString, QString> pair: stringInd)
        {
            if(pair.first.isEmpty())
                throw std::runtime_error("DyskryminatorSM::PushChar(QChar sgn): empty elemet in stringInd.first");
            idx = outBuff.indexOf(pair.first);
            if(idx>-1)
            {
                workBuff.clear();
                awaitingDoubleEnd = pair.second;
                awaitingStringException = pair.second;
                currentState = stateString;
                return;
            }
        }
        break;
    //================== ONE LINE COMMENT ===========================================
    case stateOneLineComment:
        return;
        break;
    //================== PERM COMMENT ===============================================
    case statePermComment:
        workBuff.append(sgn);
        wasComment = true;
        if(awaitingDoubleEnd.isEmpty())
            throw std::runtime_error("DyskryminatorSM::PushChar(QChar sgn): empty elemet in startEndComments.second");
        idx = workBuff.indexOf(awaitingDoubleEnd);
        if(idx>-1)
        {
            workBuff.clear();
            currentState = stateNormal;
            return;
        }
        break;
    //================== STRING =====================================================
    case stateString:
        workBuff.append(sgn);
        idx = workBuff.lastIndexOf(awaitingDoubleEnd);
        if(idx>-1)
        {
            if(!awaitingStringException.isEmpty())
            {
                int idx2 = workBuff.lastIndexOf(awaitingStringException);
                if(idx2==(idx-(awaitingStringException.size()-awaitingDoubleEnd.size())))
                    return;
            }
            outBuff.append(workBuff);
            workBuff.clear();
            currentState = stateNormal;
            return;
        }
        break;
    default:
        throw std::runtime_error("DyskryminatorSM::PushChar: unknown state");
    }
}

void DyskryminatorSM::PushEndl() throw(std::runtime_error)
{
    switch (currentState)
    {
    //================== NORMAL =====================================================
    case stateNormal:
        return;
        break;
    //================== ONE LINE COMMENT ===========================================
    case stateOneLineComment:
        currentState = stateNormal;
        return;
        break;
    //================== PERM COMMENT ===============================================
    case statePermComment:
        workBuff.clear();
        wasComment = true;
        return;
        break;
    //================== STRING =====================================================
    case stateString:
        outBuff.append(workBuff);
        workBuff.clear();
        return;
        break;
    default:
        throw std::runtime_error("DyskryminatorSM::PushChar: unknown state");
    }
}
