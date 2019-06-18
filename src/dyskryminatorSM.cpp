#include "dyskryminatorSM.hpp"
#include <QString>

/**
 * @param set - Opis znaczników wedłóg których będą usuwane komentarze.
 */
DyskryminatorSM::DyskryminatorSM(const Set* set)
{
    if(set==nullptr)
        throw std::runtime_error("DyskryminatorSM::DyskryminatorSM: nullptr as argument");
    if(!set->isValid())
        throw std::runtime_error("DyskryminatorSM::DyskryminatorSM: przekazany nieprawidłowy obiekt Set");

    oneLineComments = set->GetOneLineComments();
    startEndComments = set->GetStartEndComments();
    stringInd = set->GetStringInd();

    ResetState();
}

/**
 * Ustawia stan początkowy (czyli zwykły kod bez otwartego komentarza ani stringu).
 */
void DyskryminatorSM::ResetState()
{
    currentState = stateNormal;
    wasComment = false;
    outBuff.clear();
    workBuff.clear();
    awaitingDoubleEnd.clear();
    awaitingStringException.clear();
}

/**
 * Usuwa z podanej linii komentarze na podstawie ustawionych znaczników oraz stanu z wcześniejszych wywołań funkcji.
 * @param line - referencja do linii kodu.
 * @return true - wystąpił komentarz
 */
bool DyskryminatorSM::DyscriminateLine(QString &line)
{
    wasComment = false;
    for(QChar sgn: line)
        PushChar(sgn);
    line = PushEndl();
    return wasComment;
}

void DyskryminatorSM::PushChar(QChar sgn)
{
    int idx;
    switch (currentState)
    {
    //================== NORMAL =====================================================
    case stateNormal:
        workBuff.append(sgn);
        for(QString ol: oneLineComments)
        {
            idx = workBuff.indexOf(ol);
            if(idx>-1)
            {
                wasComment = true;
                workBuff = workBuff.remove(idx, ol.size());
                outBuff.append(workBuff);
                currentState = stateOneLineComment;
                return;
            }
        }
        for(QPair<QString, QString> pair: startEndComments)
        {
            idx = workBuff.indexOf(pair.first);
            if(idx>-1)
            {
                wasComment = true;
                workBuff = workBuff.remove(idx, pair.first.size());
                outBuff.append(workBuff);
                workBuff.clear();
                awaitingDoubleEnd = pair.second;
                currentState = statePermComment;
                return;
            }
        }
        for(QPair<QString, QString> pair: stringInd)
        {
            idx = workBuff.indexOf(pair.first);
            if(idx>-1)
            {
                outBuff.append(workBuff);
                workBuff.clear();
                awaitingDoubleEnd = pair.first;
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

QString DyskryminatorSM::PushEndl()
{
    switch (currentState)
    {
    //================== NORMAL =====================================================
    case stateNormal:
        outBuff.append(workBuff);
        workBuff.clear();
        break;
    //================== ONE LINE COMMENT ===========================================
    case stateOneLineComment:
        workBuff.clear();
        currentState = stateNormal;
        break;
    //================== PERM COMMENT ===============================================
    case statePermComment:
        workBuff.clear();
        wasComment = true;
        break;
    //================== STRING =====================================================
    case stateString:
        outBuff.append(workBuff);
        workBuff.clear();
        break;
    default:
        throw std::runtime_error("DyskryminatorSM::PushChar: unknown state");
    }
    QString temp = outBuff;
    outBuff.clear();
    return temp;
}
