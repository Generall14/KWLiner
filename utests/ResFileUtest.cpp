#include "gtest/gtest.h"

#include <QSharedPointer>
#include "src/set.hpp"
#include "src/resFile.hpp"
#include <QStringList>
#include <QPair>
#include <QVector>
#include <memory>
#include <QFile>
#include <QTextStream>

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

class DumbResFile : public ResFile
{
protected:
    virtual std::unique_ptr<QTextStream> getTextStreamFromFile(QFile &)
    {
        return std::make_unique<QTextStream>(&text);
    }
public:
    QString text = "";
};

TEST(ResFile, ConstructorValidations)
{
    DumbResFile rf1;
    EXPECT_THROW(rf1.parseFile("existing file", nullptr), std::runtime_error) << "przekazany pusty wskaźnik do konstruktora";

    DumbResFile rf2;
    SetStub invalidSet(QStringList{}, QStringList{""}, {{"", ""}}, {{"", ""}});
    EXPECT_THROW(rf2.parseFile("existing file", &invalidSet), std::runtime_error) << "przekazany błędny obiekt Set do konstruktora";

    DumbResFile rf3;
    SetStub validSet(QStringList{"existing file"}, QStringList{"fd"}, {{"dd", "ss"}}, {{"aa", "ee"}});
    EXPECT_NO_THROW(rf3.parseFile("f", &validSet)) << "prawidłowe dane";
}

TEST(ResFile, countTest)
{
    SetStub set(QStringList{".cpp"}, QStringList{"//", ";"},
                                {{"/*", "*/"}, {"XX", "XX"}},
                                {{"\"", "\\\""}});
    DumbResFile rf;
    rf.text = "\n"
              "linia \"str//ing\" nr 7\n"
            "\n"
            "li/*fds*/ni/*fds*/a nr 1\n"
            "linia nr 2/*twerter\n"
            "ytryteyt\n"
            "yteytr*/linia nr 3\n"
            "linia nr 4//428435\n"
            "linia nr 5//gr/*gs\n"
            "l/*re/*te//htr*/inia nr 6\n"
            "//vghccghghg\n"
            "/*trstgre*/\n"
            "   \n"
            "    \n"
            "            \n"
            "linia \"str//ing\" nr 7\n"
            "linia \"/*string*/\" nr 8\n"
            "linia \"\\\"//string\" nr 9\n"
            "linia nr 10\n"
            "\n"
            "\n";
    rf.parseFile("some file", &set);


    EXPECT_EQ(rf.Code(), 11);
    EXPECT_EQ(rf.Total(), 21);
    EXPECT_EQ(rf.Light(), 7);
    EXPECT_EQ(rf.Comment(), 3);
}

