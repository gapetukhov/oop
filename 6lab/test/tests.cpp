#include <gtest/gtest.h>
#include <stdexcept>
#include <memory>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include "EntityFactory.h"
#include "fightVisitor.h"
#include "conobs.h"
#include "fileObserver.h"
#include <Windows.h>


TEST(NPCTests, CreateKnightTest) {
    Knight knight("SirLancelot", 100.0f, 140.0f);
    EXPECT_EQ(knight.getType(), "Knight");
    EXPECT_EQ(knight.getName(), "SirLancelot");
    EXPECT_EQ(knight.getX(), 100.0f);
    EXPECT_EQ(knight.getY(), 140.0f);
}

TEST(NPCTests, CreateSquirrelTest) {
    Squirrel squirrel("Chipper", 50.0f, 30.0f);
    EXPECT_EQ(squirrel.getType(), "Squirrel");
    EXPECT_EQ(squirrel.getName(), "Chipper");
    EXPECT_EQ(squirrel.getX(), 50.0f);
    EXPECT_EQ(squirrel.getY(), 30.0f);
}

TEST(NPCTests, CreatePegasusTest) {
    Pegasus pegasus("SkyFlare", 200.0f, 210.0f);
    EXPECT_EQ(pegasus.getType(), "Pegasus");
    EXPECT_EQ(pegasus.getName(), "SkyFlare");
    EXPECT_EQ(pegasus.getX(), 200.0f);
    EXPECT_EQ(pegasus.getY(), 210.0f);
}

// Тесты создания с NPCFactory
TEST(NPCFactoryTests, CreateMultipleKnightsTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto knight1 = EntityFactory::createNPC("Knight", "SirLancelot", 100.0f, 140.0f, npcs);
    auto knight2 = EntityFactory::createNPC("Knight", "SirArthur", 120.0f, 150.0f, npcs);
    EXPECT_EQ(knight1->getType(), "Knight");
    EXPECT_EQ(knight2->getType(), "Knight");
    EXPECT_EQ(knight1->getName(), "SirLancelot");
    EXPECT_EQ(knight2->getName(), "SirArthur");
}

TEST(NPCFactoryTests, CreateMultipleSquirrelsTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto squirrel1 = EntityFactory::createNPC("Squirrel", "Chipper", 50.0f, 30.0f, npcs);
    auto squirrel2 = EntityFactory::createNPC("Squirrel", "Nutty", 60.0f, 40.0f, npcs);
    EXPECT_EQ(squirrel1->getType(), "Squirrel");
    EXPECT_EQ(squirrel2->getType(), "Squirrel");
    EXPECT_EQ(squirrel1->getName(), "Chipper");
    EXPECT_EQ(squirrel2->getName(), "Nutty");
}

TEST(NPCFactoryTests, CreateMultiplePegasusesTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto pegasus1 = EntityFactory::createNPC("Pegasus", "SkyFlare", 200.0f, 210.0f, npcs);
    auto pegasus2 = EntityFactory::createNPC("Pegasus", "SilverWing", 220.0f, 230.0f, npcs);
    EXPECT_EQ(pegasus1->getType(), "Pegasus");
    EXPECT_EQ(pegasus2->getType(), "Pegasus");
    EXPECT_EQ(pegasus1->getName(), "SkyFlare");
    EXPECT_EQ(pegasus2->getName(), "SilverWing");
}


TEST(FightVisitorTests, LogFileWritingTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(std::make_shared<Squirrel>("Nutty", 1, 2));
    npcs.push_back(std::make_shared<Knight>("SirGalahad", 3, 4));

    FightVisitor fightVisitor{5.0f};
    std::shared_ptr<FileObserver> fileObserver = std::make_shared<FileObserver>("battle_log.txt");
    fightVisitor.addObserver(fileObserver);
    fightVisitor.fight(npcs);

    std::ifstream logFile("battle_log.txt");
    std::string logLine;

    bool fightLogged = false;
    while (std::getline(logFile, logLine)) {
        if (logLine.find("FIGHT INITIATED") != std::string::npos) {
            fightLogged = true;
            break;
        }
    }

    EXPECT_TRUE(fightLogged) << "Fight log not found in file.";
}

TEST(FightVisitorTests, NoBattleOccurredTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(std::make_shared<Squirrel>("Nutty", 1, 1));
    npcs.push_back(std::make_shared<Squirrel>("Chipper", 10, 10));

    FightVisitor fightVisitor{2.0f};
    std::shared_ptr<ConObs> Obs = std::make_shared<ConObs>();
    fightVisitor.addObserver(Obs);
    fightVisitor.fight(npcs);

    EXPECT_EQ(npcs.size(), 2); 
}

TEST(NPCFactoryTests, InvalidNPCTypeTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    EXPECT_THROW(EntityFactory::createNPC("Dragon", "FireBreath", 300.0f, 100.0f, npcs), std::invalid_argument);
}

TEST(NPCFactoryTests, CreateNPCWithNegativeCoordinatesTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    EXPECT_THROW(EntityFactory::createNPC("Squirrel", "Nutty", -150.0f, -150.0f, npcs), std::out_of_range);
}


TEST(NPCFactoryTests, CreateNPCWithInvalidNegativeXTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    EXPECT_THROW(EntityFactory::createNPC("Knight", "Lance", -100.0f, 100.0f, npcs), std::out_of_range);
}

TEST(NPCFactoryTests, CreateNPCWithInvalidNegativeYTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    EXPECT_THROW(EntityFactory::createNPC("Squirrel", "Nutty", 100.0f, -100.0f, npcs), std::out_of_range);
}

TEST(NPCFactoryTests, CorrectNPCCreationTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto npc = EntityFactory::createNPC("Pegasus", "Thunder", 150.0f, 250.0f, npcs);
    EXPECT_EQ(npc->getName(), "Thunder");
    EXPECT_EQ(npc->getX(), 150.0f);
    EXPECT_EQ(npc->getY(), 250.0f);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
