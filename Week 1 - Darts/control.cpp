#include "darts501.h"
#include <iostream>

Darts::Control::Control()
{
    getGameMode();
    
}

void Darts::Control::getGameMode()
{
    std::cout << "Welcome to Darts 501!\n";
    std::cout << "Please select a game mode:\n\n";
    std::cout << "1. 501 match between Joe and sid\n";
    std::cout << " - Sid starts first\n - score starts at 501\n - first to 3 games wins a set\n - first to 7 sets wins the match\n\n";
    std::cout << "2. Custom Game Settings\n";
    std::cout << " - Choose who starts first\n - choose starting score\n - choose how many games to win a set\n - choose how many sets to win a match\n";
    std::cout << " - change player accuracies\n\n";
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
                mode = GameMode::S_AND_J_SIM;
                break;
            }
            else if (choice == 2)
            {
                mode = GameMode::CUSTOMISED;
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

void Darts::Control::playMatches()
{

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
