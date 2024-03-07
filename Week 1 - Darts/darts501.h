#pragma once
#include <vector>
#include <string>

namespace Darts {

    class Player
    {
    private:
        int score{ 0 }; // Initial score set to 0
        int thrown{ 0 }; // Count of darts thrown
        double accuracy; // Player's accuracy percentage
        ::std::string name; // Player's name
        ::std::vector<double> accuracies; // Vector to store accuracies over rounds

        // Function to generate a random number between min and max using the Mersenne Twister engine
        int random(int min, int max);

    public:
        // Constructor to initialize a player with accuracy and name
        Player(double a, ::std::string n);

        // Getter methods
        int getScore();
        int getThrown();
        double getRoundAverage();
        double getAccuracy();
        ::std::vector<double> getAccuracies();
        ::std::string getName();

        // Method to simulate a dart throw
        void throwDart();

        // Method to simulate a round of darts
        void playRound();

        // Method to format a win message
        ::std::string win();

        // Resets player's score and thrown count for a new game
        void newGame();

        // Records the average accuracy of throws
        void appendAverage();
    };

    // Class to manage the dart game logic and players
    class DartGame
    {
    private:
        ::std::vector<Player*> players; // Vector of player pointers
        int games{ 0 }; // Count of games played
        int gamesToPlay; // Total number of games to play

    public:
        // Constructor to initialize the game with players and the number of games
        DartGame(::std::vector<Player*> p, int g);

        // Simulates the entire game
        void simulateGame();

        // Calculates and displays the average accuracy for each player across all games
        void calculateAccuracy();

        // Appends average accuracy of each game
        void appendAverage();
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
        Control();

        // Gets the game mode from the user
        void getGameMode();

        // Plays a simulated game between Joe and Sid
        void playSimulatedGame();

        // Gets the number of players from the user
        void getPlayerCount();

        // Gets the number of games to play from the user
        void getGamesToPlay();

        // Prompts the user for player names and accuracies
        void getPlayers();

        // Destructor to free memory allocated to player pointers
        ~Control();
    };
}