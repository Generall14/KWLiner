#ifndef DYSKRYMINATOR_HPP
#define DYSKRYMINATOR_HPP

#include "set.hpp"
#include "dyskryminatorSM.hpp"

class Dyskryminator
{
public:
    Dyskryminator(const Set* set);

    void ResetState();
    void DyscriminateLine(QString &line, bool *wasComment = nullptr);

private:
    DyskryminatorSM stateMachine;
};

#endif
