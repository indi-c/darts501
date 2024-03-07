#include "darts501.h"
#include <random>
#include <cmath>

Darts::Player::Player(double a, std::string n) : accuracy{ a }, name{ n }, score{ 0 }, thrown{ 0 }
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

void Darts::Player::simpleThrowDart()
{
    if (score < 10)
    {
        ++thrown;
        if (random(1, 100) <= accuracy)
        {
            ++score;
        }
    }
}

void Darts::Player::playRound()
{
    for (int i{ 0 }; i < 3; ++i)
    {
        simpleThrowDart();
    }
}

std::string Darts::Player::win()
{
    return name + " wins with " + std::to_string(thrown) + " throws and an average accuracy of " + std::to_string(round(getRoundAverage()));
}

void Darts::Player::newGame()
{
    score = 0;
    thrown = 0;
}

void Darts::Player::addAverage(int games)
{
    totalAccuracy = ((totalAccuracy * (games - 1)) + getRoundAverage()) / games;
}

int Darts::Player::throw_bull() {

    // Throw for the bull 

    int r = random(1, 100);

    if (r <= accuracy) {
        return 50;
    }
    // threshold changed to make simulation more realistic
    // idea is that players with accuracies > 85 will always hit the outer bull
    // players with accuracies > 50 have a higher chance at hitting the outer bull as accuracy 100
    // and players with accuracies < 50 are likely to miss completely as accuracy 0
    // arbitrary but interesting
    else if (r <= (accuracy + ((accuracy - 50 ) * (accuracy * 0.005)))) {
        return 25;
    }
    // misses outer bull, hitting a random single
    else {
        return random(1, 20);
    }
}

// mostly unmodified from given code
// assumes intention of 80% accuracy originally
// code modified to fit
int Darts::Player::throw_treble(int d) {

    // Board neighbours ignoring slot zero
    int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
               {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

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
        return 3 * bd[0][d];
    }
    else if (r <= 16) {
        return 3 * bd[1][d];
    }
    else if (r <= 18) {
        return bd[0][d];
    }
    else {
        return bd[1][d];
    }

}

// mostly unmodified from given code
// now uses player accuracy value
// probabilities on miss are the same but are now independent of accuracy
int Darts::Player::throw_double(int d) {

    // Board neighbours ignoring slot zero
    int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
               {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

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
        return 2 * bd[0][d];
    }
    else if (r <= 16) {
        return 2 * bd[1][d];
    }
    else if (r <= 18) {
        return bd[0][d];
    }
    else {
        return bd[1][d];
    }
}

int Darts::Player::throw_single(int d) {

    //  return result of throwing for single d with accuracy 88% (or 80% for the outer)

    // Board neighbours ignoring slot zero
    int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
               {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

    int r = random(1, 100);

    if (d == 25) {
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
    else {
        if (r <= accuracy) {
            return d;
        }
        // 1/3 (4/12) chance as per original
        else if ((r = random(1, 12)) <= 4) {
            return bd[0][d];
        }
        // 1/3 (4/12) chance as per original
        else if (r <= 8) {
            return bd[1][d];
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
}