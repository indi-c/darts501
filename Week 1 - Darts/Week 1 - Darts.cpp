#include <iostream>
#include <random>
#include <string>
#include <vector>

// random function seeded by std::random_device
int random(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

// player class storing score, darts thrown, average, name, and accuracy
class Player
{
	private:

		int score{ 0 };
		int thrown{ 0 };
		double accuracy;
		std::string name;
		std::vector<double> accuracies;

	public:

		// constructor which takes value for accuracy
		Player(double a, std::string n) : accuracy{ a }, name{ n }, score{ 0 }, thrown{ 0 }
			{
			}
		// getters
			int getScore()
			{
				return score;
			}
			int getThrown()
			{
				return thrown;
			}
			double getAverage()
			{
				return static_cast<double>(score) / thrown * 100;
			}
			double getAccuracy()
			{
				return accuracy;
			}
			std::vector<double> getAccuracies()
			{
				return accuracies;
			}
			std::string getName()
			{
				return name;
			}
			// simulates a dart throw
			void throwDart()
			{
				if (score < 10)
				{
					++thrown;
					if (random(0, 100) <= accuracy)
					{
						++score;
					}
				}
			}
			// simulates a round of darts
			void playRound()
			{
				for (int i{ 0 }; i < 3; ++i)
				{	
					throwDart();
				}
			}

			// returns a string with the player's name and total throws
			std::string win()
			{
				return name + " wins with " + std::to_string(thrown) + " throws and an average accuracy of " + std::to_string(getAverage());
			}

			void newGame()
			{
				score = 0;
				thrown = 0;
			}

			void appendAverage()
			{
				accuracies.push_back(getAverage());
			}
};

// dart game class storing game logic, and players
class DartGame
{
	private:
		
		std::vector<Player*> players;
		int games{ 0 };
		int rounds{ 0 };
		int gamesToPlay;

	public:
		// constructor which takes a game mode and a vector of players
		DartGame(std::vector<Player*> p, int g) : players{ p }, gamesToPlay{ g }
		{
		}

		// simulates a game of darts
		void simulateGame()
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

		// calculates accuracy of each player across all games
		void calculateAccuracy()
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

		void appendAverage()
		{
			for (auto p : players)
			{
				p->appendAverage();
			}
		}
};

class Control
{
private:
	std::vector<Player*> players;
	int gamesToPlay{ 0 };
	int playerCount{ 0 };
	enum class GameMode
	{
		SIMULATED_GAME,
		CUSTOM_GAME
	};
	GameMode mode;

public:

	Control()
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

	// prompts user for game mode
	void getGameMode()
	{
		std::cout << "Welcome to Darts!\n";
		std::cout << "Please select a game mode:\n";
		std::cout << "1. Simulated Game between Joe and Sid\n";
		std::cout << "2. Custom Game Settings\n";
		std::cout << "Enter 1 or 2: ";
		int choice{ 0 };
		std::string choiceString;
		std::getline(std::cin >> std::ws, choiceString);
		// checks if choice is a valid int
		try
		{
			choice = std::stoi(choiceString);
		}
		catch (std::invalid_argument)
		{
			std::cout << "\n [*] Invalid choice. Please try again.\n";
			getGameMode();
		}
		if (choice == 1)
		{
			mode = GameMode::SIMULATED_GAME;
		}
		else if (choice == 2)
		{
			mode = GameMode::CUSTOM_GAME;
		}
		else
		{
			std::cout << "Invalid choice. Please try again." << std::endl;
			getGameMode();
		}
	}

	// plays a simulated game between Joe and Sid
	void playSimulatedGame()
	{
		Player * joe = new Player{ 71, "Joe" };
		Player * sid = new Player{ 73, "Sid" };
		std::vector<Player*> players{ joe, sid };
		DartGame game{ players, 1 };
		game.simulateGame();
		game.calculateAccuracy();
	}

	// prompts user for number of players
	void getPlayerCount()
	{
		std::cout << "How many players? ";
		std::string playerCountString;
		std::getline(std::cin >> std::ws, playerCountString);
		// checks if playerCount is a valid int
		try
		{
			playerCount = std::stoi(playerCountString);
		}
		catch (std::invalid_argument)
		{
			std::cout << "\n [*] Invalid number of players. Please try again.\n";
			getPlayerCount();
		}
		if (playerCount < 2)
		{
			std::cout << "\n [*] Invalid number of players. Please try again.\n";
			getPlayerCount();
		}
	}

	// prompts user for number of games to play
	void getGamesToPlay()
	{
		std::cout << "How many games? ";
		std::string	gamesToPlayString;
		std::getline(std::cin >> std::ws, gamesToPlayString);
		// checks if gamesToPlay is a valid int
		try
		{
			gamesToPlay = std::stoi(gamesToPlayString);
		}
		catch (std::invalid_argument)
		{
			std::cout << "\n [*] Invalid number of games. Please try again.\n";
			getGamesToPlay();
		}
		if (gamesToPlay < 1)
		{
			std::cout << "\n [*] Invalid number of games. Please try again.\n";
			getGamesToPlay();
		}
	}

	// prompts user for player names and accuracies
	void getPlayers()
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
			std::cout << "Enter player " << i + 1 << "'s accuracy: ";
			std::getline(std::cin >> std::ws, accuracyString);
			// checks if accuracy is a valid double
			try
			{
				accuracy = std::stod(accuracyString);
			}
			catch (std::invalid_argument)
			{
				std::cout << "\n [*] Invalid accuracy. Please try again.\n";
				getPlayers();
			}
			Player * player = new Player{ accuracy, name };
			players.push_back(player);
		}
	}
};

int main()
{
    Control control;
}