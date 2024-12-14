#include "pegasus.h"

Pegasus::Pegasus(const std::string& name, float x, float y) : NPC(name, x, y) {}

std::string Pegasus::getType() const { return "Pegasus"; }
bool Pegasus::canFightWith(const NPC& other) const {
    return false; 
}
bool Pegasus::willWin(const NPC& other) const {
    return false; 
}
