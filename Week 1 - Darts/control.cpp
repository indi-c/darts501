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

void Darts::Control::getRepetitions()
{
    // while loop to check if the input is a valid number
    while (true)
    {
        std::cout << "How many matches should be played? ";
        std::string matchesToPlayString;
        std::getline(std::cin >> std::ws, matchesToPlayString);

        try
        {
            rules.repetitions = std::stoi(matchesToPlayString);
            if (rules.repetitions > 0)
            {
                break;
            }
            std::cout << "\n [*] Invalid number of matches. Please try again.\n";
        }
        catch (std::invalid_argument)
        {
            std::cout << "\n [*] Invalid number of matches. Please try again.\n";
        }

    }
}

void Darts::Control::getPlayerAccuracies()
{
    std::cout << "Enter player accuracies\n";
    std::cout << "Accuracy must be a number between 0 and 100\n";

    std::string accuracyString;
    double accuracies[2];

    std::string names[2] = { "Joe", "Sid" };

    for (int i{ 0 }; i < 2; ++i)
    {
        // while loop to check if the input is a valid number
        while (true)
        {
            std::cout << "Enter " << names[i] << "'s accuracy: ";
            std::getline(std::cin >> std::ws, accuracyString);

            try
            {
                accuracies[i] = std::stod(accuracyString);
                if (accuracies[i] >= 0 && accuracies[i] <= 100)
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
    }

    players.playerOne = Player(accuracies[0], names[0]);
    players.playerTwo = Player(accuracies[1], names[1]);
}


Darts::Control::~Control()
{
}
