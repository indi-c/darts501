#pragma once
#include <string>

// interface for darts501 which stores all classes and structs in Darts namespace

namespace Darts {

    class Player
    {
    private:
        int score{}; // to be set by dartGame
        int thrown{ 0 }; // Count of darts thrown
        double accuracy; // Player's accuracy percentage
        ::std::string name; // Player's name
        double totalAccuracy{}; // double to store the average accuracy of throws

        // Function pointer type for dart throws
        typedef void (*dartThrow)(int);
        
        // struct to store the throw type and target
        // target should be 25 for outer bull, 50 for inner bull, otherwise 1-20
        typedef struct Throw
        {
            int target;
            dartThrow throwType;
        } Throw;

        // Function to decide which throw to make
        // Returns a struct containing the throw type and target
        Throw decideThrow(); 

        // board representation thanks to code given for task
        int board[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
               {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

        // Function to generate a random number between min and max using the Mersenne Twister engine
        int random(int min, int max);

    public:

        // Default constructor to initialize a player
        Player();

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
        int throwBull(int d);

        // throw for a treble
        int throwTreble(int d);

        // throw for a double
        int throwDouble(int d);

        // throw for a single
        int throwSingle(int d);
    };

    // struct to store the two players and order
    typedef struct GamePlayers
    {
        Player playerOne;
        Player playerTwo;
        enum class Order
        {
			PLAYER_ONE,
			PLAYER_TWO
		} order;
    } GamePlayers;

    // struct to store the rules of the game
    typedef struct Ruleset
    {
        int startPoints;
        int gamesToWin;
        int setsToWin;
        int repetitions;
    } Ruleset;

    // Class to manage the dart game logic and players
    class DartGame
    {
    private:

        GamePlayers players;
        Ruleset rules;

        int gameCount{ 1 }; // Count of games played

    public:
        // Constructor to initialize the game with players and the number of games
        DartGame(GamePlayers p, Ruleset r);

        // Simulates the entire game
        void simulateMatch();

        // Calculates and displays the average accuracy for each player across all games
        void displayAccuracies();

        // Appends average accuracy of each game
        void addAverages();
    };

    // Control class to manage the game setup and mode selection
    class Control
    {
    private:
        enum class GameMode // Enum for game mode selection
        {
            S_AND_J_SIM,
            CUSTOMISED
        };
        GameMode mode; // Current game mode
        Ruleset rules; // Rules of the game
        GamePlayers players; // Players in the game

    public:
        // Constructor to initiate the game setup process
        Control();

        // Gets the game mode from the user
        void getGameMode();

        // plays as many matches as specified by the user
        void playMatches();

        // input repetitions
        void inputRepetitions();

        // input player accuracies
        void inputPlayerAccuracies();

        // input round starting points
        void inputStartPoints();

        // input games to win a set
        void inputGamesToWin();

        // input sets to win the match
        void inputSetsToWin();

        // Destructor if needed
        ~Control();
    };
}