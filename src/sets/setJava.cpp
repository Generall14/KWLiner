#include "setJava.hpp"

SetJava::SetJava():
    Set("Java")
{
    _suffixes = QStringList{".java"};
    _oneLlineComm = QStringList{"//"};
    _seComm.append(QPair<QString, QString>("/*", "*/"));
    _striInd.append(QPair<QString, QString>("\"", "\\\""));
}
