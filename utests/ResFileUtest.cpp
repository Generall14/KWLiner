#include "gtest/gtest.h"

#include <QSharedPointer>
#include "src/set.hpp"
#include "src/resFile.hpp"
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

//TEST(ResFile, ConstructorValidations) <TODO> bez sensu bez wstrzyknięcia własnego QFile
//{
//    EXPECT_THROW(ResFile::ParseFile("existing file", nullptr), std::runtime_error) << "przekazany pusty wskaźnik do konstruktora";

//    SetStub invalidSet(QStringList{}, QStringList{""}, {{"", ""}}, {{"", ""}});
//    EXPECT_THROW(ResFile::ParseFile("existing file", &invalidSet), std::runtime_error) << "przekazany błędny obiekt Set do konstruktora";

//    SetStub validSet(QStringList{"existing file"}, QStringList{"fd"}, {{"dd", "ss"}}, {{"aa", "ee"}});
//    EXPECT_NO_THROW(ResFile::ParseFile("f", &validSet)) << "prawidłowe dane";
//}
