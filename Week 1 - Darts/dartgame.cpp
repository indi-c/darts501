#include "darts501.h"
#include <iostream>

Darts::DartGame::DartGame(::std::vector<Player*> p, int g) : players{ p }, gamesToPlay{ g }
{
}

void Darts::DartGame::simulateGame()
{
    for (games; games <= gamesToPlay; ++games)
    {
        for (auto p : players)
        {
            p->newGame();
        }
        bool gameWon{ false };
        while (!gameWon)
        {
            for (auto p : players)
            {
                p->playRound();
                if (p->getScore() >= 10)
                {
                    gameWon = true;
                    std::cout << p->win() << std::endl;
                    addAverages();
                    break;
                }
            }
        }
    }
}

void Darts::DartGame::displayAccuracies()
{
    for (auto p : players)
    {
        std::cout << p->getName() << " has an average accuracy of " << p->getTotalAccuracy() << std::endl;
    }
}

void Darts::DartGame::addAverages()
{
    for (auto p : players)
    {
        p->addAverage();
    }
}