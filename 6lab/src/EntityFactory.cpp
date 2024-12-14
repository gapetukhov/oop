#include "EntityFactory.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

bool EntityFactory::areCorrectCoords(float x, float y) {
    return x >= 0 && x <= 500 && y >= 0 && y <= 500;
}

bool EntityFactory::isUnique(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& name, float x, float y) {
    for (const auto& npc : npcs) {
        if (npc->getName() == name || (npc->getX() == x && npc->getY() == y)) {
            return false;
        }
    }
    return true;
}

std::shared_ptr<NPC> EntityFactory::createNPC(const std::string& type, const std::string& name, float x, float y, const std::vector<std::shared_ptr<NPC>>& npcs) {
    if (!areCorrectCoords(x, y)) {
        throw std::out_of_range("Координаты должны быть в пределах 0 <= x, y <= 500.");
    }

    if (type == "Pegasus") return std::make_shared<Pegasus>(name, x, y);
    if (type == "Squirrel") return std::make_shared<Squirrel>(name, x, y);
    if (type == "Knight") return std::make_shared<Knight>(name, x, y);

    throw std::invalid_argument("Npc ошибка");
}

std::vector<std::shared_ptr<NPC>> EntityFactory::loadFromFile(const std::string& filename, const std::vector<std::shared_ptr<NPC>>& existingNpcs) {
    std::vector<std::shared_ptr<NPC>> npcs = existingNpcs;
    std::cout << "Попытка открыть файл: " << filename << "\n";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл '" << filename << "'\n";
    }

    std::cout << "Файл успешно открыт: " << filename << "\n";

    std::string type, name;
    float x, y;

    while (file >> type >> name >> x >> y) {
        if (!areCorrectCoords(x, y)) {
            throw std::runtime_error("Неверные координаты NPC в файле:(" + std::to_string(x) + ", " + std::to_string(y) + ")");
        }
        if (!isUnique(npcs, name, x, y)) {
            throw std::runtime_error("Повторяющееся имя или координаты в файле:" + name);
        }

        auto newNPC = createNPC(type, name, x, y, npcs);
        npcs.push_back(newNPC);

        std::cout << "NPC загружен: " << name << " (" << type << ") на координатах (" << x << ", " << y << ").\n";
    }

    file.close();
    return npcs;
}
