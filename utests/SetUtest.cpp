#include "gtest/gtest.h"

#include <QSharedPointer>
#include "src/set.hpp"
#include "src/sets/setCpp.hpp"
#include <QStringList>
#include <QPair>
#include <QVector>


// Sprawdza czy wszystkie elementy zwrócone przez Set::GetSetsList() są obsługiwane w Set::GetSet(...).
TEST(Set, AllGetSetsListInGetSet)
{
    for(auto str: Set::GetSetsList())
    {
        EXPECT_NO_THROW(Set::GetSet(str));
    }
}

// Sprawdzanie czy zwracane obiekty z Set::GetSetsList() są poprawnego typu
TEST(Set, ReturnedTypesFromGetSet)
{
    for(auto str: Set::GetSetsList())
    {
        EXPECT_EQ(Set::GetSet(str).data()->GetName(), str);
    }
}

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

TEST(Set, isValid)
{
    SetStub validSet(QStringList{".a", ".b"}, QStringList{"//"}, {{"dd", "ff"}}, {{"dd", ""}});
    EXPECT_TRUE(validSet.isValid());
}

TEST(Set, isValid_NoSuffixes)
{
    SetStub invalidSet(QStringList{}, QStringList{"//"}, {{"dd", "ff"}}, {{"dd", ""}});
    EXPECT_FALSE(invalidSet.isValid());
}

TEST(Set, isValid_EmptySuffixes)
{
    SetStub invalidSet(QStringList{"", "f"}, QStringList{"//"}, {{"dd", "ff"}}, {{"dd", ""}});
    EXPECT_FALSE(invalidSet.isValid());
}

TEST(Set, isValid_EmptyOneLineComm)
{
    SetStub invalidSet(QStringList{"r", "f"}, QStringList{""}, {{"dd", "ff"}}, {{"dd", ""}});
    EXPECT_FALSE(invalidSet.isValid());
}

TEST(Set, isValid_EmptyContinousComm)
{
    SetStub invalidSet(QStringList{"r", "f"}, QStringList{"f"}, {{"", "ff"}}, {{"dd", ""}});
    EXPECT_FALSE(invalidSet.isValid());

    SetStub invalidSet2(QStringList{"r", "f"}, QStringList{"f"}, {{"gf", ""}}, {{"dd", ""}});
    EXPECT_FALSE(invalidSet2.isValid());
}

TEST(Set, isValid_EmptyStringInd)
{
    SetStub invalidSet(QStringList{"r", "f"}, QStringList{"fds"}, {{"dd", "ff"}}, {{"", ""}});
    EXPECT_FALSE(invalidSet.isValid());
}
