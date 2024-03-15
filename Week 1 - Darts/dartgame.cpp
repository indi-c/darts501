#include "darts501.h"
#include <iostream>

Darts::DartGame::DartGame(GamePlayers p, Ruleset r) : players{ p }, rules{ r }
{
}

void Darts::DartGame::simulateMatch()
{
    while (players.playerOne.getSetsWon() < 7 && players.playerTwo.getSetsWon() < 7)
    {
		simulateSet();
	}
}

void Darts::DartGame::simulateSet()
{
	while (players.playerOne.getGamesWon() < 3 && players.playerTwo.getGamesWon() < 3)
	{
		simulateGame();
	}
}

void Darts::DartGame::simulateGame()
{
	// reset player scores and thrown count
	for (auto p : players.players)
	{
		p->newGame(rules.startPoints);
	}

	while (players.playerOne.getScore() > 0 && players.playerTwo.getScore() > 0)
	{
		simulateRound();
	}
}

void Darts::DartGame::simulateRound()
{
	static Player *activePlayer{ &players.players[(int)players.ToPlay] };
	
	// throw and verify three scores
	for (int i{ 0 }; i < 3; ++i)
	{
		ThrowVerification verified{ ThrowVerification::INVALID };
		while (verified == ThrowVerification::INVALID)
		{
			activePlayer->throwDart();
			verified = verifyScore(activePlayer);
		}

		if (verified == ThrowVerification::WIN)
		{
			// player won the game
			activePlayer->incrementGamesWon();
			return;
		}
	}

	// switch active player
	players.ToPlay = (players.ToPlay == GamePlayers::ToPlay::PLAYER_ONE) ? GamePlayers::ToPlay::PLAYER_TWO : GamePlayers::ToPlay::PLAYER_ONE;
	activePlayer = { &players.players[(int)players.ToPlay] };
}

void Darts::DartGame::displayAccuracies()
{
    std::cout << players.playerOne.getName() << " has an average accuracy of " << round(p->getTotalAccuracy()) << '\n';
    std::cout << players.playerTwo.getName() << " has an average accuracy of " << round(p->getTotalAccuracy()) << '\n';
}