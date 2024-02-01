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

	public:

		// constructor which takes value for accuracy
		Player(double a, std::string n) : accuracy{ a }, name{ n }
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
				return static_cast<double>(score) / thrown;
			}
			double getAccuracy()
			{
				return accuracy;
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
				else win();
			
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
				return name + " wins with " + std::to_string(thrown) + " throws!";
			}
};

// dart game class storing game logic, game mode, and players
class DartGame
{
	private:
		enum class GameMode
		{
			SIMULATED_GAME,
			CUSTOM_GAME
		};
		GameMode mode;
		std::vector<Player> players;

	public:
		// constructor which takes a game mode and a vector of players
		DartGame(GameMode m, std::vector<Player> p) : mode{ m }, players{ p }
		{
		}
};

int main()
{
    std::cout << "Hello World!\n";
}
