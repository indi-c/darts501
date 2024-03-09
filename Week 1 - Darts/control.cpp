#include "darts501.h"
#include <iostream>
#include <thread>
#include <vector>

Darts::Control::Control()
{
    getGameMode();
    if (mode == GameMode::CUSTOMISED)
	{
		inputPlayerAccuracies();
		inputRepetitions();
		inputStartPoints();
		inputGamesToWin();
		inputSetsToWin();
	}
	else
	{
		inputRepetitions();
        rules.gamesToWin = 3;
        rules.setsToWin = 7;
        rules.startPoints = 501;
        players.playerOne = Player(80, "Joe");
        players.playerTwo = Player(80, "Sid");
        players.order = GamePlayers::Order::PLAYER_TWO; // sid goes first
	}
    playMatches();
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
    // get number of threads supported by the system
    int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0)
    {
        numThreads = 1;
    }

    // remainderRepetitions is the number of repetitions that will be left over after the repetitions are divided by the number of threads
    int remainderRepetitions{ (rules.repetitions % numThreads) };
    // subtract the remainder from the total repetitions leaving a multiple of the number of threads
    rules.repetitions -= remainderRepetitions;

    // vector to store the threads
    std::vector<std::thread> threads;
    // vector to store the games
    std::vector<DartGame> games;

    // create the games for the remainder repetitions
    for (int i{ 0 }; i < remainderRepetitions; ++i)
    {
        games.push_back(DartGame(players, rules));
    }

    // create the threads for DartGame::simulateMatch for the remainder repetitions
    for (int i{ 0 }; i < remainderRepetitions; ++i)
    {
        threads.push_back(std::thread(&DartGame::simulateMatch, &games[i]));
    }

    // join the threads
    for (auto& th : threads)
    {
        if (th.joinable())
        {
            th.join();
        }
    }

    // clear the threads vector
    threads.clear();

    // resize the threads vector to the number of repetitions
    threads.resize(numThreads);

    // clear the games vector
    games.clear();

    // resize the games vector to the number of threads
    games.resize(numThreads);

	// create games and threads for the remaining repetitions in multiples of the number of threads
    for (int i{ rules.repetitions }; i > 0; i -= numThreads)
    {
        // create the games for each thread
        for (int j{ 0 }; j < numThreads; ++j)
        {
            games[j] = DartGame(players, rules);
        }

        // create the threads for DartGame::simulateMatch for each game
        for (int j{ 0 }; j < numThreads; ++j)
		{
            threads[j] = std::thread(&DartGame::simulateMatch, &games[j]);
		}

        // join the threads
        for (auto& th : threads)
		{
			if (th.joinable())
			{
				th.join();
			}
		}

        // clear vectors
        threads.clear();
        games.clear();
    }
}

void Darts::Control::inputRepetitions()
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

void Darts::Control::inputPlayerAccuracies()
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

void Darts::Control::inputRepetitions()
{
    std::string repetitionsString;
    // while loop to check if the input is a valid number
    while (true)
    {
		std::cout << "How many matches should be played? ";
		std::getline(std::cin >> std::ws, repetitionsString);

		try
		{
			rules.repetitions = std::stoi(repetitionsString);
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

void Darts::Control::inputGamesToWin()
{
    std::string GamesToWinString;

    // while loop to check if the input is a valid number
    while (true)
	{
		std::cout << "How many games should be won to win a set? ";
		std::getline(std::cin >> std::ws, GamesToWinString);

		try
		{
			rules.gamesToWin = std::stoi(GamesToWinString);
			if (rules.gamesToWin > 0)
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

void Darts::Control::inputSetsToWin()
{
    std::string SetsToWinString;

    // while loop to check if the input is a valid number
    while (true)
    {
        std::cout << "How many sets should be won to win the match? ";
        std::getline(std::cin >> std::ws, SetsToWinString);

        try
        {
            rules.setsToWin = std::stoi(SetsToWinString);
            if (rules.setsToWin > 0)
            {
                break;
            }
            std::cout << "\n [*] Invalid number of sets. Please try again.\n";
        }
        catch (std::invalid_argument)
        {
            std::cout << "\n [*] Invalid number of sets. Please try again.\n";
        }
    }
}

void Darts::Control::inputStartPoints()
{
    std::string StartPointsString;

    // while loop to check if the input is a valid number
    while (true)
	{
		std::cout << "What should the starting score be? ";
		std::getline(std::cin >> std::ws, StartPointsString);

		try
		{
			rules.startPoints = std::stoi(StartPointsString);
			if (rules.startPoints > 0)
			{
				break;
			}
			std::cout << "\n [*] Invalid starting score. Please try again.\n";
		}
		catch (std::invalid_argument)
		{
			std::cout << "\n [*] Invalid starting score. Please try again.\n";
		}
	}
}

Darts::Control::~Control()
{
}
