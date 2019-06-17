#include "gtest/gtest.h"

#include <QSharedPointer>
#include "src/set.hpp"
#include "src/dyskryminatorSM.hpp"
#include <QStringList>
#include <QPair>
#include <QVector>

class SetStub : public Set
{
public:
    using dvec = QVector<QPair<QString, QString> >;
    SetStub(QStringList suffixes, QStringList oneLlineComm, dvec seComm, dvec striInd):
        Set("stub")
    {
        _suffixes = suffixes;
        _oneLlineComm = oneLlineComm;
        _seComm = seComm;
        _striInd = striInd;
    }
};

TEST(DyskryminatorSM, NullSetThrowsError)
{
    EXPECT_THROW(new DyskryminatorSM(nullptr), std::runtime_error);
}

// Sprawdza czy wszystkie elementy zwrócone przez Set::GetSetsList() są obsługiwane w Set::GetSet(...).
//TEST(DyskryminatorSM, AllGetSetsListInGetSet)
//{
//    for(auto str: Set::GetSetsList())
//    {
//        EXPECT_NO_THROW(Set::GetSet(str));
//    }
//}
