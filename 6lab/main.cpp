#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "EntityFactory.h"
#include "fightVisitor.h"
#include "conobs.h"
#include "fileObserver.h"
#include <Windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::vector<std::shared_ptr<NPC>> npcs;
    FightVisitor fightVisitor(0.0f);
    fightVisitor.addObserver(std::make_shared<ConObs>());
    fightVisitor.addObserver(std::make_shared<FileObserver>("log.txt"));

    while (true) {
        std::cout << "1. Новый перс\n"
                  << "2. Загрузить перса из файла\n"
                  << "3. Сохранить npc в файл\n"
                  << "4. Отчёт персонажей\n"
                  << "5. Битва\n"
                  << "6. Выход\n"
                  << "Введите ваш выбор: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string type, name;
            float x, y;

            std::cout << "Введите тип NPC (Knight, Squirrel, Pegasus): ";
            std::cin >> type;
            std::cout << "Введите имя NPC: ";
            std::cin >> name;
            std::cout << "Введите координаты NPC (x y): ";
            std::cin >> x >> y;

            try {
                auto newNPC = EntityFactory::createNPC(type, name, x, y, npcs);
                npcs.push_back(newNPC);
                std::cout << "NPC успешно добавлен: " << name << " (" << type << ") на координатах (" << x << ", " << y << ").\n";
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при добавлении NPC: " << e.what() << "\n";
            }

        } else if (choice == 2) {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;

            try {
                std::cout << "Попытка загрузить NPC из файла...\n";
                auto loadedNPCs = EntityFactory::loadFromFile(filename, npcs);

                std::cout << "NPC успешно загружены из файла: " << filename << "\n";
                for (size_t i = npcs.size(); i < loadedNPCs.size(); i++) {
                    std::cout << "NPC загружен: " << loadedNPCs[i]->getName()
                              << " (" << loadedNPCs[i]->getType() << ") на координатах (" 
                              << loadedNPCs[i]->getX() << ", " << loadedNPCs[i]->getY() << ").\n";
                }
                npcs = std::move(loadedNPCs);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при загрузке из файла: " << e.what() << "\n";
            }

        } else if (choice == 3) {
            std::string filename;
            std::cout << "Введите имя файла для сохранения: ";
            std::cin >> filename;

            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Ошибка: невозможно открыть файл для записи.\n";
                continue;
            }

            for (const auto& npc : npcs) {
                file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
            }
            file.close();
            std::cout << "NPC успешно сохранены в файл " << filename << ".\n";

        } else if (choice == 4) {
            if (npcs.empty()) {
                std::cout << "Нет добавленных NPC.\n";
            } else {
                std::cout << "Список NPC:\n";
                for (const auto& npc : npcs) {
                    std::cout << npc->getType() << " " << npc->getName()
                              << " (" << npc->getX() << ", " << npc->getY() << ")\n";
                }
            }

        } else if (choice == 5) {
            float range;
            std::cout << "Введите дальность для сражений NPC: ";
            std::cin >> range;

            if (range <= 0) {
                std::cerr << "Ошибка: дальность должна быть положительным числом.\n";
                continue;
            }

            fightVisitor = FightVisitor(range);
            fightVisitor.addObserver(std::make_shared<ConObs>());
            fightVisitor.addObserver(std::make_shared<FileObserver>("log.txt"));

            fightVisitor.fight(npcs);
            std::cout << "Боевое сражение завершено.\n";

        } else if (choice == 6) {
            std::cout << "Завершение программы.\n";
            break;
        } else {
            std::cerr << "Ошибка: некорректный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
