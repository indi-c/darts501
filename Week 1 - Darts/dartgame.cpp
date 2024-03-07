#include "darts501.h"
#include <iostream>

Darts::DartGame::DartGame(::std::vector<Player*> p, int g) : players{ p }, gamesToPlay{ g }
{
}

void Darts::DartGame::simulateGame()
{
    for (games; games < gamesToPlay; ++games)
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
                    appendAverage();
                    break;
                }
            }
        }
    }
}

void Darts::DartGame::calculateAccuracy()
{
    for (auto p : players)
    {
        double totalAccuracy{ 0 };
        for (auto a : p->getAccuracies())
        {
            totalAccuracy += a;
        }
        std::cout << p->getName() << " has an average accuracy of " << totalAccuracy / games << std::endl;
    }
}

void Darts::DartGame::appendAverage()
{
    for (auto p : players)
    {
        p->appendAverage();
    }
}