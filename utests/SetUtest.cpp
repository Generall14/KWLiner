#include "gtest/gtest.h"

#include <QSharedPointer>
#include "src/set.hpp"
#include "src/sets/setCpp.hpp"

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
