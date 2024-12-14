#include "knight.h"

Knight::Knight(const std::string& name, float x, float y) : NPC(name, x, y) {}

std::string Knight::getType() const { return "Knight"; }

bool Knight::canFightWith(const NPC& other) const {
    return other.getType() == "Squirrel" || other.getType() == "Knight";
}

bool Knight::willWin(const NPC& other) const {
    if (other.getType() == "Knight") {
        return false; 
    }
    return other.getType() == "Squirrel"; 
}
