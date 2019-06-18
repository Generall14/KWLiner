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
        return std::make_unique<QTextStream>();
    }
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

//<TODO> dalej testować!
