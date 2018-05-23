#include "setCpp.hpp"

SetCpp::SetCpp():
    Set("c/c++")
{
    _suffixes = QStringList{".c", ".cpp", ".h", ".hpp"};
    _oneLlineComm = QStringList{"//"};
    _seComm.append(QPair<QString, QString>("/*", "*/"));
}
