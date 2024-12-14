#ifndef KNIGHT_H
#define KNIGHT_H
#include "npc.h"

class Knight : public NPC {
public:
    Knight(const std::string& name, float x, float y);
    std::string getType() const override;
    bool canFightWith(const NPC& other) const override;
    bool willWin(const NPC& other) const override;
};

#endif 