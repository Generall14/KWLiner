#include "setPIC.hpp"

SetPIC::SetPIC():
    Set("PIC asm")
{
    _suffixes = QStringList{".asm", ".inc"};
    _oneLlineComm = QStringList{"//", ";"};
    _seComm.append(QPair<QString, QString>("/*", "*/"));
    _striInd.append(QPair<QString, QString>("\"", "\\\""));
}
