#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include <memory>
#include <vector>
#include "npc.h"
#include "knight.h"
#include "squirrel.h"
#include "pegasus.h"

class EntityFactory {
private:
    static bool areCorrectCoords(float x, float y);
    static bool isUnique(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& name, float x, float y);

public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, float x, float y,const std::vector<std::shared_ptr<NPC>>& npcs);
    static std::vector<std::shared_ptr<NPC>> loadFromFile(const std::string& filename,const std::vector<std::shared_ptr<NPC>>& existingNpcs);
};

#endif 
