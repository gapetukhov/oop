#ifndef FIGHTVISITOR_H
#define FIGHTVISITOR_H

#include <vector>
#include <memory>
#include "npc.h"
#include "observer.h"

class FightVisitor {
    float range;
    std::vector<std::shared_ptr<Obs>> observers;

public:
    FightVisitor(float range);
    void addObserver(std::shared_ptr<Obs> observer);
    void fight(std::vector<std::shared_ptr<NPC>>& npcs);
};

#endif 
