#include "darts501.h"
#include <iostream>

Darts::Control::Control()
{
    getGameMode();
    if (mode == GameMode::SIMULATED_GAME)
    {
        playSimulatedGame();
    }
    else if (mode == GameMode::CUSTOM_GAME)
    {
        getPlayerCount();
        getGamesToPlay();
        getPlayers();
        DartGame game{ players, gamesToPlay };
        game.simulateGame();
        game.calculateAccuracy();
    }
}

void Darts::Control::getGameMode()
{
    std::cout << "Welcome to Darts!\n";
    std::cout << "Please select a game mode:\n";
    std::cout << "1. Simulated Game between Joe and Sid\n";
    std::cout << "2. Custom Game Settings\n";
    std::cout << "Enter 1 or 2: ";
    int choice{ 0 };
    std::string choiceString;
    // while loop to check if the input is a valid number
    while (true)
    {
        std::getline(std::cin >> std::ws, choiceString);
        try
        {
            choice = std::stoi(choiceString);
            if (choice == 1)
            {
                mode = GameMode::SIMULATED_GAME;
                break;
            }
            else if (choice == 2)
            {
                mode = GameMode::CUSTOM_GAME;
                break;
            }
            std::cout << "\n [*] Invalid choice. Please try again.\n";
        }
        catch (std::invalid_argument)
        {
            std::cout << "\n [*] Invalid choice. Please try again.\n";
        }
    }
}

void Darts::Control::playSimulatedGame()
{
    Player* joe = new Player{ 71, "Joe" };
    Player* sid = new Player{ 73, "Sid" };
    std::vector<Player*> players{ joe, sid };
    DartGame game{ players, 1 };
    game.simulateGame();
    game.calculateAccuracy();
}

void Darts::Control::getPlayerCount()
{
    // while loop to check if the input is a valid number
    while (true)
    {
        std::cout << "How many players? ";
        std::string playerCountString;
        std::getline(std::cin >> std::ws, playerCountString);

        try
        {
            playerCount = std::stoi(playerCountString);
            if (playerCount > 0)
            {
                break;
            }
            std::cout << "\n [*] Invalid number of players. Please try again.\n";
        }
        catch (std::invalid_argument)
        {
            std::cout << "\n [*] Invalid number of players. Please try again.\n";
        }
    }
}

void Darts::Control::getGamesToPlay()
{
    // while loop to check if the input is a valid number
    while (true)
    {
        std::cout << "How many games? ";
        std::string gamesToPlayString;
        std::getline(std::cin >> std::ws, gamesToPlayString);

        try
        {
            gamesToPlay = std::stoi(gamesToPlayString);
            if (gamesToPlay > 0)
            {
                break;
            }
            std::cout << "\n [*] Invalid number of games. Please try again.\n";
        }
        catch (std::invalid_argument)
        {
            std::cout << "\n [*] Invalid number of games. Please try again.\n";
        }

    }
}

void Darts::Control::getPlayers()
{
    std::cout << "Enter player names and accuracies\n";
    std::cout << "Accuracy must be a number between 0 and 100\n";
    std::cout << "Players will play in the order they are entered\n";

    for (int i{ 0 }; i < playerCount; ++i)
    {
        std::string name;
        std::string accuracyString;
        double accuracy;
        std::cout << "Enter player " << i + 1 << "'s name: ";
        std::getline(std::cin >> std::ws, name);
        // while loop to check if the input is a valid number
        while (true)
        {
            std::cout << "Enter player " << i + 1 << "'s accuracy: ";
            std::getline(std::cin >> std::ws, accuracyString);

            try
            {
                accuracy = std::stod(accuracyString);
                if (accuracy >= 0 && accuracy <= 100)
                {
                    break;
                }
                std::cout << "\n [*] Invalid accuracy. Please try again.\n";
            }
            catch (std::invalid_argument)
            {
                std::cout << "\n [*] Invalid accuracy. Please try again.\n";
            }
        }

        Player* player = new Player{ accuracy, name };
        players.push_back(player);
    }
}


Darts::Control::~Control()
{
        for (auto p : players)
        {
            delete p;
        }
}
