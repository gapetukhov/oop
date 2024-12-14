#ifndef PEGASUS_H
#define PEGASUS_H
#include "npc.h"

class Pegasus : public NPC {
public:
    Pegasus(const std::string& name, float x, float y);
    std::string getType() const override;
    bool canFightWith(const NPC& other) const override;
    bool willWin(const NPC& other) const override;
};

#endif 
