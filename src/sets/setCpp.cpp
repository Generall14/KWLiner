#include "setCpp.hpp"

SetCpp::SetCpp():
    Set("C/C++")
{
    _suffixes = QStringList{".c", ".cpp", ".h", ".hpp"};
    _oneLlineComm = QStringList{"//"};
    _seComm.append(QPair<QString, QString>("/*", "*/"));
    _striInd.append(QPair<QString, QString>("\"", "\\\""));
}
