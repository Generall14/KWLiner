#include "gtest/gtest.h"

#include "src/set.hpp"

// Sprawdza czy wszystkie elementy zwrócone przez Set::GetSetsList() są obsługiwane w Set::GetSet(...).
TEST(Set, AllGetSetsListInGetSet)
{
    for(auto str: Set::GetSetsList())
    {
        Set* s = nullptr;
        EXPECT_NO_THROW(Set::GetSet(str));
        delete s;
    }
}
