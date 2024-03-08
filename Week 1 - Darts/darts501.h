#pragma once
#include <vector>
#include <string>

namespace Darts {

    class Player
    {
    private:
        int score{}; // to be set by dartGame
        int thrown{ 0 }; // Count of darts thrown
        double accuracy; // Player's accuracy percentage
        ::std::string name; // Player's name
        double totalAccuracy{}; // double to store the average accuracy of throws

        // board representation thanks to code given for task
        int board[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
               {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

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
        double getTotalAccuracy();
        ::std::string getName();

        // Resets player's score and thrown count for a new game
        void newGame(int score);

        // average new accuracy into the total accuracy
        void addAverage(int games);

        // throw at the bull
        int throw_bull();

        // throw for a treble
        int throw_treble(int d);

        // throw for a double
        int throw_double(int d);

        // throw for a single
        int throw_single(int d);
    };

    // struct to store the two players and order
    typedef struct gamePlayers
    {
        Player* playerOne;
        Player* playerTwo;
    } gamePlayers;

    // struct to store the rules of the game
    typedef struct ruleSet
    {
        int startPoints;
        int gamesToWin;
        int setsToWin;
        int repetitions;
    } ruleSet;

    // Class to manage the dart game logic and players
    class DartGame
    {
    private:

        struct gamePlayers players;
        int games{ 1 }; // Count of games played
        int gamesToPlay; // Total number of games to play

    public:
        // Constructor to initialize the game with players and the number of games
        DartGame(gamePlayers p, int g);

        // Simulates the entire game
        void simulateGame();

        // Calculates and displays the average accuracy for each player across all games
        void displayAccuracies();

        // Appends average accuracy of each game
        void addAverages();
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