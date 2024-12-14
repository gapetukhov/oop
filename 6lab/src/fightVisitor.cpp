#include "fightVisitor.h"
#include <algorithm>
#include <iostream>

FightVisitor::FightVisitor(float range) : range(range) {}

void FightVisitor::addObserver(std::shared_ptr<Obs> observer) {
    observers.push_back(observer);
}

void FightVisitor::fight(std::vector<std::shared_ptr<NPC>>& npcs) {
    bool battleOccurred = false;

    for (size_t i = 0; i < npcs.size(); i++) {
        for (size_t j = i + 1; j < npcs.size(); j++) {
            auto& npc1 = npcs[i];
            auto& npc2 = npcs[j];

            if (npc1->distanceTo(*npc2) <= range &&
                npc1->canFightWith(*npc2) && npc2->canFightWith(*npc1)) {
                battleOccurred = true;
                std::string fightLog = "FIGHT INITIATED: " + npc1->getName() + " (" + npc1->getType() + ") vs " +
                                       npc2->getName() + " (" + npc2->getType() + ") -> ";

                bool npc1Wins = npc1->willWin(*npc2);
                bool npc2Wins = npc2->willWin(*npc1);

                if (!npc1Wins && !npc2Wins) {
                    fightLog += "It's a draw.";
                    std::cout << fightLog << std::endl;

                    for (auto& observer : observers) {
                        observer->notify(fightLog);
                    }

                    npcs.erase(npcs.begin() + j);
                    npcs.erase(npcs.begin() + i);
                    i = -1; 
                    break;
                } else if (npc1Wins && npc2Wins) {
                    fightLog += "Both died.";
                    std::cout << fightLog << std::endl;


                    for (auto& observer : observers) {
                        observer->notify(fightLog);
                    }

                    npcs.erase(npcs.begin() + j);
                    npcs.erase(npcs.begin() + i);
                    i = -1; 
                    break;
                } else if (npc1Wins) {
                    fightLog += npc1->getName() + " won.";
                    std::cout << fightLog << std::endl;

                    for (auto& observer : observers) {
                        observer->notify(fightLog);
                    }

                    npcs.erase(npcs.begin() + j);
                    --j; 
                } else {
                    fightLog += npc2->getName() + " won.";
                    std::cout << fightLog << std::endl;

                    for (auto& observer : observers) {
                        observer->notify(fightLog);
                    }

                    npcs.erase(npcs.begin() + i);
                    i = -1; 
                    break;
                }
            } else {
                std::string reason = "can't fight: ";
                if (npc1->distanceTo(*npc2) > range) {
                    reason += "too far apart.";
                } else if (!npc1->canFightWith(*npc2) || !npc2->canFightWith(*npc1)) {
                    reason += "incompatible fighting types.";
                }
                std::string fightLog = npc1->getName() + " and " + npc2->getName() + " " + reason;

                for (auto& observer : observers) {
                    observer->notify(fightLog);
                }
            }
        }
    }
    if (!battleOccurred) {
        std::string noBattleLog = "No battle.";
        for (auto& observer : observers) {
            observer->notify(noBattleLog);
        }
    }
}
