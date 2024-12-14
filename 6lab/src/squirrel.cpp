#include "squirrel.h"

Squirrel::Squirrel(const std::string& name, float x, float y) : NPC(name, x, y) {}

std::string Squirrel::getType() const { return "Squirrel"; }

bool Squirrel::canFightWith(const NPC& other) const {
    return other.getType() == "Pegasus" || other.getType() == "Squirrel" || other.getType() == "Knight";
}
bool Squirrel::willWin(const NPC& other) const {
    if (other.getType() == "Squirrel") {
        return true;
    }
    return other.getType() == "Pegasus"; 
}
