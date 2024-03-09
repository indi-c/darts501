#include "darts501.h"
#include <random>
#include <cmath>

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
int Darts::Player::getThrown() { return thrown; }
double Darts::Player::getRoundAverage() { return static_cast<double>(score) / thrown * 100; }
double Darts::Player::getAccuracy() { return accuracy; }
double Darts::Player::getTotalAccuracy() { return totalAccuracy; }
std::string Darts::Player::getName() { return name; }

void Darts::Player::newGame(int score)
{
    this->score = score;
    thrown = 0;
}

void Darts::Player::addAverage(int games)
{
    totalAccuracy = ((totalAccuracy * (games - 1)) + getRoundAverage()) / games;
}

// moved outerbull here to allow for api consistency

int Darts::Player::throwBull(int d) {

    // Throw for the bull 

    int r = random(1, 100);

    if (d == 50)
    {
        if (r <= accuracy) {
            return 50;
        }
        // threshold changed to make simulation more realistic
        // idea is that players with accuracies > 85 will always hit the outer bull
        // players with accuracies > 50 have a higher chance at hitting the outer bull as accuracy 100
        // and players with accuracies < 50 are likely to miss completely as accuracy 0
        // arbitrary but interesting
        else if (r <= (accuracy + ((accuracy - 50) * (accuracy * 0.005)))) {
            return 25;
        }
        // misses outer bull, hitting a random single
        else {
            return random(1, 20);
        }
    }
    else
    {
        if (r <= accuracy) {
            return 25;
        }
        // 50% chance of bullseye miss (assuming 50% chance of even number)
        // as per original design but inclusive of accuracy
        else if (r % 2 == 0) {
            return 50;
        }
        // 50% chance of single miss
        else {
            return random(1, 20);
        }
    }
}

// mostly unmodified from given code
// assumes intention of 80% accuracy originally
// code modified to fit
int Darts::Player::throwTreble(int d) {

    int r = random(1, 100);

    if (r <= accuracy) {
        return 3 * d;
    }

    // intentions unsure but changed to reflect an assumed intention
    // that the accuracy was 80% and as such a single was 50% etc.
    else if ((r = random(1, 20) <= 10)) {
        return d;
    }
    else if (r <= 13) {
        return 3 * board[0][d];
    }
    else if (r <= 16) {
        return 3 * board[1][d];
    }
    else if (r <= 18) {
        return board[0][d];
    }
    else {
        return board[1][d];
    }

}

// mostly unmodified from given code
// now uses player accuracy value
// probabilities on miss are the same but are now independent of accuracy
int Darts::Player::throwDouble(int d) {

    int r = random(1, 100);

    if (r <= accuracy) {
        return 2 * d;
    }

    // following values use the same probability as the original code on miss
    else if ((r = random(1, 20) <= 5)) {
        return 0;
    }
    else if (r <= 10) {
        return d;
    }
    else if (r <= 13) {
        return 2 * board[0][d];
    }
    else if (r <= 16) {
        return 2 * board[1][d];
    }
    else if (r <= 18) {
        return board[0][d];
    }
    else {
        return board[1][d];
    }
}

int Darts::Player::throwSingle(int d) {

    //  return result of throwing for single d with accuracy 88% (or 80% for the outer)

    int r = random(1, 100);

    if (r <= accuracy) {
        return d;
    }
    // 1/3 (4/12) chance as per original
    else if ((r = random(1, 12)) <= 4) {
        return board[0][d];
    }
    // 1/3 (4/12) chance as per original
    else if (r <= 8) {
        return board[1][d];
    }
    // 1/6 (2/12) chance as per original
    else if (r <= 10) {
        return 3 * d;
    }
    // 1/6 (2/12) chance as per original
    else {
        return 2 * d;
    }
}

Darts::Player::Throw Darts::Player::decideThrow()
{

}