#include "setMSP.hpp"

SetMSP::SetMSP():
    Set("MSP430 asm")
{
    _suffixes = QStringList{".s43", ".h"};
    _oneLlineComm = QStringList{"//", ";"};
    _seComm.append(QPair<QString, QString>("/*", "*/"));
    _striInd.append(QPair<QString, QString>("\"", "\\\""));
}
