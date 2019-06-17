#include "setPython.hpp"

SetPython::SetPython():
    Set("Python")
{
    _suffixes = QStringList{".py"};
    _oneLlineComm = QStringList{"#"};
    //_seComm.append(QPair<QString, QString>());
    _striInd.append(QPair<QString, QString>("\"", "\\\""));
    _striInd.append(QPair<QString, QString>("'", "\'"));//<TODO> co z """ / ''' ?
}
