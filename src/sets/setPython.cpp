#include "setPython.hpp"

SetPython::SetPython():
    Set("Python")
{
    _suffixes = QStringList{".py"};
    _oneLlineComm = QStringList{"#"};
    //_seComm.append(QPair<QString, QString>());
}
