#include "darts501.h"
#include <random>

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
std::vector<double> Darts::Player::getAccuracies() { return accuracies; }
std::string Darts::Player::getName() { return name; }

void Darts::Player::throwDart()
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
        throwDart();
    }
}

std::string Darts::Player::win()
{
    return name + " wins with " + std::to_string(thrown) + " throws and an average accuracy of " + std::to_string(getRoundAverage());
}

void Darts::Player::newGame()
{
    score = 0;
    thrown = 0;
}

void Darts::Player::appendAverage()
{
    accuracies.push_back(getRoundAverage());
}