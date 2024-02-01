#include <iostream>
#include <random>
#include <string>
#include <vector>

// Function to generate a random number between min and max using the Mersenne Twister engine
int random(int min, int max)
{
    static std::random_device rd; // Non-deterministic seed
    static std::mt19937 mt(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(min, max); // Distribution in range [min, max]
    return dist(mt); // Return a random number within the specified range
}

// Class to represent a player in the dart game
class Player
{
private:
    int score{ 0 }; // Initial score set to 0
    int thrown{ 0 }; // Count of darts thrown
    double accuracy; // Player's accuracy percentage
    std::string name; // Player's name
    std::vector<double> accuracies; // Vector to store accuracies over rounds

public:
    // Constructor to initialize a player with accuracy and name
    Player(double a, std::string n) : accuracy{ a }, name{ n }, score{ 0 }, thrown{ 0 }
    {
    }

    // Getter methods
    int getScore() { return score; }
    int getThrown() { return thrown; }
    double getAverage() { return static_cast<double>(score) / thrown * 100; }
    double getAccuracy() { return accuracy; }
    std::vector<double> getAccuracies() { return accuracies; }
    std::string getName() { return name; }

    // Method to simulate a dart throw
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

    // Method to simulate a round of darts
    void playRound()
    {
        for (int i{ 0 }; i < 3; ++i)
        {
            throwDart();
        }
    }

    // Method to format a win message
    std::string win()
    {
        return name + " wins with " + std::to_string(thrown) + " throws and an average accuracy of " + std::to_string(getAverage());
    }

    // Resets player's score and thrown count for a new game
    void newGame()
    {
        score = 0;
        thrown = 0;
    }

    // Records the average accuracy of throws
    void appendAverage()
    {
        accuracies.push_back(getAverage());
    }
};

// Class to manage the dart game logic and players
class DartGame
{
private:
    std::vector<Player*> players; // Vector of player pointers
    int games{ 0 }; // Count of games played
    int gamesToPlay; // Total number of games to play

public:
    // Constructor to initialize the game with players and the number of games
    DartGame(std::vector<Player*> p, int g) : players{ p }, gamesToPlay{ g }
    {
    }

    // Simulates the entire game
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

    // Calculates and displays the average accuracy for each player across all games
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

    // Appends average accuracy of each game
    void appendAverage()
    {
        for (auto p : players)
        {
            p->appendAverage();
        }
    }
};

// Control class to manage the game setup and mode selection
class Control
{
private:
    std::vector<Player*> players; // Vector of player pointers
    int gamesToPlay{ 0 }; // Number of games to play
    int playerCount{ 0 }; // Number of players
    enum class GameMode // Enum for game mode selection
    {
        SIMULATED_GAME,
        CUSTOM_GAME
    };
    GameMode mode; // Current game mode

public:
    // Constructor to initiate the game setup process
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

    // Gets the game mode from the user
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

    // Plays a simulated game between Joe and Sid
    void playSimulatedGame()
    {
        Player* joe = new Player{ 71, "Joe" };
        Player* sid = new Player{ 73, "Sid" };
        std::vector<Player*> players{ joe, sid };
        DartGame game{ players, 1 };
        game.simulateGame();
        game.calculateAccuracy();
    }

    // Gets the number of players from the user
    void getPlayerCount()
    {
        std::cout << "How many players? ";
        std::string playerCountString;
        std::getline(std::cin >> std::ws, playerCountString);
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

    // Gets the number of games to play from the user
    void getGamesToPlay()
    {
        std::cout << "How many games? ";
        std::string gamesToPlayString;
        std::getline(std::cin >> std::ws, gamesToPlayString);
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

    // Prompts the user for player names and accuracies
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
            try
            {
                accuracy = std::stod(accuracyString);
            }
            catch (std::invalid_argument)
            {
                std::cout << "\n [*] Invalid accuracy. Please try again.\n";
                getPlayers();
            }
            Player* player = new Player{ accuracy, name };
            players.push_back(player);
        }
    }

    // Destructor to free memory allocated to player pointers
    ~Control()
    {
        for (auto p : players)
        {
			delete p;
		}
	}
};

int main()
{
    Control control; // Instantiates the Control class to start the game
}