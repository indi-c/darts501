#pragma once
#include <string>
#include <mutex>
#include <array>
#include <vector>

// interface for darts501 which stores all classes and structs in Darts namespace

namespace Darts {

    class Player
    {
    private:
        int score{}; // to be set by dartGame
        int throwScore{}; // used to track the score a throw gives
        int gamesWon{}; // to be incremented by dartGame
        int setsWon{}; // to be incremented by dartGame

        int thrown{ 0 }; // Count of darts thrown
        double accuracy{}; // Player's accuracy percentage
        ::std::string name{}; // Player's name
        double totalAccuracy{}; // double to store the average accuracy of throws

        // Function pointer type for dart throws
        // used in struct Throw to store the throw type
        typedef void (Darts::Player::*dartThrow)(int);
        
        // struct to store the throw type and target
        // target should be 25 for outer bull, 50 for inner bull, otherwise 1-20
        typedef struct Throw
        {
            int target;
            dartThrow throwType;
            int idealScore; // what score should this throw be at
        } Throw;

        // vectors to score a bruteforce of scores and optimal throws
        // this relies on the practical assumption each player
        // is confident in their accuracy and will always aim for the optimum throw
        // rather than worrying about safety or the other player
        std::vector<Throw> throwsToOneSeventy;
        std::vector<Throw> threeThrowWins;
        std::vector<Throw> twoThrowWins;
        std::vector<Throw> oneThrowWins;

        // function to calculate throws
        // run on construction
        // placing my trust in the exponential allocation of std::vector
        void calculateThrows();

        // Function to decide which throw to make
        // Returns a struct containing the throw type and target
        Throw decideThrow(); 

        // throw at the bull, 25 for outer, 50 for inner
        void throwBull(int d);

        // throw for a treble
        void throwTreble(int d);

        // throw for a double
        void throwDouble(int d);

        // throw for a single
        void throwSingle(int d);

        // board representation thanks to code given for task
        const int board[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
               {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

        // Function to generate a random number between min and max using the Mersenne Twister engine
        int random(int min, int max);

    public:

        // Default constructor to initialize a player
        Player();

        // Constructor to initialize a player with accuracy and name
        Player(double a, ::std::string n);

        // Getter methods
        // Scores
        int getScore();
        int getThrowScore();
        int getSetsWon();
        int getGamesWon();

        int getThrown();
        double getRoundAverage();
        double getAccuracy();
        double getTotalAccuracy();
        ::std::string getName();

        // increment score, gamesWon, setsWon;
        void incrementGamesWon();
        void incrementSetsWon();

        // Resets player's score and thrown count for a new game
        void newGame(int score);

        // throws a dart by deciding strategy and applying it
        void throwDart();
    };

    // struct to store the two players and who is to play
    class GamePlayers
    {
    public:
        Player playerOne;
        Player playerTwo;
        std::array<Player, 2> players{ playerOne, playerTwo };
        enum class ToPlay
        {
            PLAYER_ONE,
            PLAYER_TWO
        } ToPlay;
    };


    // remove inheritance from GamePlayers
    // use composition instead
    class PlayerStats
    {
    private:

        // number of games played
        int repetitions{}; 

        // accuracy of each player
        double playerOneAccuracy;
        double playerTwoAccuracy;

        // average accuracy of each player
        double playerOneAverage;
        double playerTwoAverage;

        // match wins for each player
        int playerOneWins;
        int playerTwoWins;

    public:

        GamePlayers players;

        // getter methods
        double getPlayerOneAverage();
        double getPlayerTwoAverage();

        int getPlayerOneWins();
        int getPlayerTwoWins();

		// setter methods
        void setRepetitions(int r);
        void setPlayerOneAccuracy(double a);
        void setPlayerTwoAccuracy(double a);
		void setPlayerOneWins(int w);
		void setPlayerTwoWins(int w);

		// Constructor to initialize the player stats
		PlayerStats(GamePlayers p);
    };

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

        enum class ThrowVerification
		{
			INVALID,
			VALID,
            WIN
		};

    public:
        // Constructor to initialize the game with players and the number of games
        DartGame(GamePlayers p, Ruleset r);

        // Simulates the entire game
        void simulateMatch();

        // Simulates a single set
        void simulateSet();

        // Simulates a single game
        void simulateGame();

        // Simulates a single round
        void simulateRound();

        // Calculates and displays the average accuracy for each player across all games
        void displayAccuracies();

        // Appends average accuracy of each game
        void addAverages();

        // verifies a player's score post dart throw
        ThrowVerification verifyScore(Player *p);
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

        // mutex for thread safety used in simulateMatches
        ::std::mutex mutexMatchCount;

        int matchCount{ 1 }; // Count of matches played

    public:
        // Constructor to initiate the game setup process
        Control();

        // Gets the game mode from the user
        void getGameMode();

        // creates threads for the matches and joins them
        void createMatchThreads();

        // loop for threaded matches called by simulateMatches
        // loops through number of repetitions and calls simulateMatch decrementing each time
        void simulateMatches();

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