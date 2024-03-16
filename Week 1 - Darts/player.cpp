#include "darts501.h"
#include <random>
#include <cmath>
#include <array>

Darts::Player::Player(double a, std::string n) : accuracy{ a }, name{ n }, thrown{ 0 }
{
}

Darts::Player::Player()
{
}

int Darts::Player::random(int min, int max)
{
    static std::random_device rd; // Non-deterministic seed
    std::seed_seq seed{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // Seed sequence
    static std::mt19937 mt(seed); // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(min, max); // Distribution in range [min, max]
    return dist(mt); // Return a random number within the specified range
}

// Getter member functions

int Darts::Player::getScore() { return score; }
int Darts::Player::getThrowScore() { return throwScore; }
int Darts::Player::getSetsWon() { return setsWon; }
int Darts::Player::getGamesWon() { return gamesWon; }
int Darts::Player::getThrown() { return thrown; }
double Darts::Player::getRoundAverage() { return static_cast<double>(score) / thrown * 100; }
double Darts::Player::getAccuracy() { return accuracy; }
double Darts::Player::getTotalAccuracy() { return totalAccuracy; }
std::string Darts::Player::getName() { return name; }

// increment member functions
void Darts::Player::incrementGamesWon() { gamesWon++; }
void Darts::Player::incrementSetsWon() { setsWon++; }

void Darts::Player::newGame(int score)
{
    this->score = score;
    thrown = 0;
}

// calculates optimal throw
Darts::Player::Throw Darts::Player::calculateOptimalThrow()
{
    // prioritize finishing on double 20 or double 16 if possible
    if (score == 40 || score == 32)
    {
        return Throw{ score / 2, throwDouble };
    }
    // inner bull finish
    else if (score == 50)
    {
        return Throw{ 50, throwBull };
    }
    // even scores below 40 get double finish
    else if ((score < 40 && (score % 2) == 0))
    {
        return Throw{ score / 2, throwDouble };
    }
    // if score is 74 go for treble 14 to leave 32
    else if (score == 74)
    {
        return Throw{ 14, throwTreble };
    }
    // else if score is 61 go for treble 7 to leave 40
    else if (score == 61)
    {
        return Throw{ 7, throwTreble };
    }
    // more aggressive plays if the opponent can finish
    else if (score > 61 && enemyScore <= 170)
    {
        // rudimentary, aims for treble 20 to get into double range asap
        return Throw{ 20, throwTreble };
    }
    // scores above 61 and less than 170
    else if (score > 61 && score <= 170)
    {
        if (score % 2 == 0 && score <= 170)
        {
            return Throw{ 20, throwTreble };
        }
        else if (score < 170)
        {
            // treble 19, guaranteeing an even score trying to get into a lower range
            return Throw{ 19, throwTreble };
        }
    }
    // scores less than 61 but above 40
    else if (score < 61 && score > 40)
    {
        // aim for a score that leaves you with 40
        return Throw{ score - 40, throwSingle };
    }
    // handling odd scores below 40 by reducing them to an even score for a double finish
    else if (score < 40 && (score % 2) != 0)
    {
        // single 1 to get to an even score for a double finish
        return Throw{ 1, throwSingle };
    }
    // default to treble 20
    else
    {
        return Throw{ 20, throwTreble };
    }
}

// calculate simple complexity throw
Darts::Player::Throw Darts::Player::calculateSimpleThrow()
{
    // if game is able to be finished with a double, aim to finish game
    if ((score <= 40) && ((score % 2) == 0))
    {
        return Throw{ score / 2, throwDouble };
    }
    // if odd and below 40 throw a single 1
    else if ((score <= 40) && ((score % 2) != 0))
    {
        return Throw{ 1, throwSingle };
    }
    // if game is able to be finished with inner bull, aim to finish game
    else if (score == 50)
    {
        return Throw{ 50, throwBull };
    }
    // aims for single to get into double range due to safety
    // score must be above 41
    else if ((score <= 60) && (score > 41))
    {
        return Throw{ score - 40, throwSingle };
    }
    // else if score is 41 throw for single 19
    // misses score 7 or 3 ensuring it'll always be even
    else if (score == 41)
    {
        return Throw{ 19, throwSingle };
    }
    // else if score is 61 throw for single 19
    // misses score 7 or 3 ensuring it'll always be even
    else if (score == 61)
    {
        return Throw{ 19, throwSingle };
    }
    // throw a triple 20 to get into range of the above if above 61
    else if (score > 61)
    {
        return Throw{ 20, throwTreble };
    }
}

// throws a dart by deciding throw and calling the appropriate function
void Darts::Player::throwDart()
{
	// decide throw
	Throw t = decideThrow();

    (this->*(t.throwType))(t.target);
}

// analyse game state and decide throw
Darts::Player::Throw Darts::Player::decideThrow()
{
    switch (difficulty)
    {
        case ThrowComplexity::SIMPLE: 
            return calculateSimpleThrow();
        case ThrowComplexity::COMPLEX:
            return calculateOptimalThrow();
    }
}

// moved outerbull here to allow for interface consistency
// function changed due to odd behaviour in provided code
void Darts::Player::throwBull(int d) {

    // Throw for the bull 

    int r = random(1, 100);

    if (d == 50)
    {
        if (r <= accuracy) {
            throwScore = 50;
        }
        // threshold changed to make simulation more realistic
        // idea is that players with accuracies > 85 will always hit the outer bull
        // players with accuracies > 50 have a higher chance at hitting the outer bull as accuracy 100
        // and players with accuracies < 50 are likely to miss completely as accuracy 0
        // arbitrary but interesting
        else if (r <= (accuracy + ((accuracy - 50) * (accuracy * 0.005)))) {
            throwScore = 25;
        }
        // misses outer bull, hitting a random single
        else {
            throwScore = random(1, 20);
        }
    }
    else
    {
        if (r <= accuracy) {
            throwScore = 25;
        }
        // 50% chance of bullseye miss (assuming 50% chance of even number)
        // as per original design but inclusive of accuracy
        else if (r % 2 == 0) {
            throwScore = 50;
        }
        // 50% chance of single miss
        else {
            throwScore = random(1, 20);
        }
    }
}

// mostly unmodified from given code
// assumes intention of 80% accuracy originally
// code modified to fit
void Darts::Player::throwTreble(int d) {

    int r = random(1, 100);

    if (r <= accuracy) {
        throwScore = 3 * d;
    }

    // intentions unsure but changed to reflect an assumed intention
    // that the accuracy was 80% and as such a single was 50% etc.
    else if ((r = random(1, 20) <= 10)) {
        throwScore = d;
    }
    else if (r <= 13) {
        throwScore = 3 * board[0][d];
    }
    else if (r <= 16) {
        throwScore = 3 * board[1][d];
    }
    else if (r <= 18) {
        throwScore = board[0][d];
    }
    else {
        throwScore = board[1][d];
    }

}

// mostly unmodified from given code
// now uses player accuracy value
// probabilities on miss are the same but are now independent of accuracy
void Darts::Player::throwDouble(int d) {

    int r = random(1, 100);

    // accuracy + 5 to simulate the ease of hitting a double compared to a treble
    if (r <= accuracy + 5) {
        throwScore = 2 * d;
    }

    // following values use the same probability as the original code on miss
    else if ((r = random(1, 20) <= 5)) {
        throwScore = 0;
    }
    else if (r <= 10) {
        throwScore = d;
    }
    else if (r <= 13) {
        throwScore = 2 * board[0][d];
    }
    else if (r <= 16) {
        throwScore = 2 * board[1][d];
    }
    else if (r <= 18) {
        throwScore = board[0][d];
    }
    else {
        throwScore = board[1][d];
    }
}

void Darts::Player::throwSingle(int d) {

    int r = random(1, 100);

    // accuracy + 10 to simulate the ease of hitting a single compared to a double or treble
    if (r <= accuracy + 10) {
        throwScore = d;
    }
    // 1/3 (4/12) chance as per original
    else if ((r = random(1, 12)) <= 4) {
        throwScore = board[0][d];
    }
    // 1/3 (4/12) chance as per original
    else if (r <= 8) {
        throwScore = board[1][d];
    }
    // 1/6 (2/12) chance as per original
    else if (r <= 10) {
        throwScore = 3 * d;
    }
    // 1/6 (2/12) chance as per original
    else {
        throwScore = 2 * d;
    }
}