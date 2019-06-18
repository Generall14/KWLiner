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

TEST(DyskryminatorSM, ConstructorValidations)
{
    EXPECT_THROW(new DyskryminatorSM(nullptr), std::runtime_error) << "przekazany pusty wskaźnik do konstruktora";

    SetStub invalidSet(QStringList{}, QStringList{""}, {{"", ""}}, {{"", ""}});
    EXPECT_THROW(new DyskryminatorSM(&invalidSet), std::runtime_error) << "przekazany błędny obiekt Set do konstruktora";
}

class FixtureDyskryminatorSM : public testing::Test
{
    protected:
    void SetUp() override
    {
        set = new SetStub(QStringList{".cpp"}, QStringList{"//", ";"},
                            {{"/*", "*/"}, {"XX", "XX"}},
                            {{"\"", "\\\""}});
        sm = new DyskryminatorSM(set);
    }

    void TearDown() override
    {
        delete set;
        set = nullptr;
        delete sm;
        sm = nullptr;
    }
    Set* set = nullptr;
    DyskryminatorSM* sm = nullptr;
    QString inout;
};

TEST_F(FixtureDyskryminatorSM, NothingSpecialInLine)
{
    inout = "1:jakas tam linia kodu";
    EXPECT_FALSE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas tam linia kodu");
}

TEST_F(FixtureDyskryminatorSM, OneLineComment)
{
    inout = "1:jakas tam linia kodu//fds";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas tam linia kodu");

    inout = "2:jakas tam linia kodu";
    EXPECT_FALSE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "2:jakas tam linia kodu");
}

TEST_F(FixtureDyskryminatorSM, ConstCommentsinLine)
{
    inout = "1:ja/*gfdg*/kas/*gg*/ t/**/am linia kodu";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas tam linia kodu");
}

TEST_F(FixtureDyskryminatorSM, ConstCommentsBetweenLine)
{
    inout = "1:jakas tam linia kodu/*gfd";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas tam linia kodu");

    inout = "2:jakas tam linia kodu";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "");

    inout = "fdsgsdfg*/3:jakas tam linia kodu";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "3:jakas tam linia kodu");
}

TEST_F(FixtureDyskryminatorSM, MixedComments)
{
    inout = "1:jakas tam linia kodu//fd/*ff";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas tam linia kodu");

    inout = "2:ja/*re/*te//htr*/kas tam linia kodu";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "2:jakas tam linia kodu");
}

TEST_F(FixtureDyskryminatorSM, EverythingIsCommented)
{
    inout = "//1:jakas tam linia kodu";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "");

    inout = "/*2:jakas tam linia kodu*/";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "");
}

TEST_F(FixtureDyskryminatorSM, CommentInSimpleString)
{
    inout = "1:jakas \"tam l//inia\" kodu";
    EXPECT_FALSE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas \"tam l//inia\" kodu");

    inout = "1:jakas \"tam l/*inia\" kodu";
    EXPECT_FALSE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas \"tam l/*inia\" kodu");
}

TEST_F(FixtureDyskryminatorSM, IndicatorInsideString)
{
    inout = "1:jakas \"ta\\\"m lini//a\" kodu";
    EXPECT_FALSE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas \"ta\\\"m lini//a\" kodu");
}

TEST_F(FixtureDyskryminatorSM, MultiLineString)
{
    inout = "1:jakas \"tam li//nia kodu";
    EXPECT_FALSE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas \"tam li//nia kodu");

    inout = "2:jakas tam li//nia kodu";
    EXPECT_FALSE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "2:jakas tam li//nia kodu");

    inout = "3:jakas tam linia kodu\"//fdsfdsfds";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "3:jakas tam linia kodu\"");
}

TEST_F(FixtureDyskryminatorSM, StringIndicatorInComments)
{
    inout = "1:jakas tam linia kodu//fd\"";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas tam linia kodu");

    inout = "2:jakas tam linia kodu//fd";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "2:jakas tam linia kodu");
}

TEST_F(FixtureDyskryminatorSM, EqualConstCommentsIndicators)
{
    inout = "1:jakas tXXdsfdsXXam linia kodu";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "1:jakas tam linia kodu");

    inout = "2:jakas tXXXXam linia kodu";
    EXPECT_TRUE(sm->DyscriminateLine(inout));
    EXPECT_EQ(inout, "2:jakas tam linia kodu");
}
