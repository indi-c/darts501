#include "darts501.h"
#include <iostream>
#include <cmath>

Darts::DartGame::DartGame(gamePlayers p, Ruleset r) : players{ p }, rules{ r }
{
}

void Darts::DartGame::simulateGame()
{
    
}

void Darts::DartGame::displayAccuracies()
{
    std::cout << players.playerOne->getName() << " has an average accuracy of " << round(p->getTotalAccuracy()) << '\n';
    std::cout << players.playerTwo->getName() << " has an average accuracy of " << round(p->getTotalAccuracy()) << '\n';
}

void Darts::DartGame::addAverages()
{
        players.playerOne->addAverage(games);
        players.playerTwo->addAverage(games);
}