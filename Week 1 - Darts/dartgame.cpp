#include "darts501.h"
#include <iostream>

Darts::DartGame::DartGame(GamePlayers p, Ruleset r) : players{ p }, rules{ r }
{
	players.arr_players[0] = &players.playerOne;
	players.arr_players[1] = &players.playerTwo;
}

void Darts::DartGame::simulateMatch()
{
    while (players.playerOne.getSetsWon() < 7 && players.playerTwo.getSetsWon() < 7)
    {
		simulateSet();
		// switch player to start the next set
		players.ToPlay = (players.ToPlay == GamePlayers::ToPlay::PLAYER_ONE) ? GamePlayers::ToPlay::PLAYER_TWO : GamePlayers::ToPlay::PLAYER_ONE;
	}
}

void Darts::DartGame::simulateSet()
{
	while (players.playerOne.getGamesWon() < 3 && players.playerTwo.getGamesWon() < 3)
	{
		simulateGame();
	}

	// get each players sets and determine the winner
	if (players.playerOne.getGamesWon() == 3)
	{
		players.playerOne.incrementSetsWon();
	}
	else if (players.playerTwo.getGamesWon() == 3)
	{
		players.playerTwo.incrementSetsWon();
	}
	players.playerOne.newSet();
	players.playerTwo.newSet();
}

void Darts::DartGame::simulateGame()
{
	// reset player scores and thrown count
	for (auto p : players.arr_players)
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
	activePlayer = { players.arr_players[(int)(players.ToPlay)] };
	
	// throw and verify three scores
	for (int i{ 0 }; i < 3; ++i)
	{
		ThrowVerification verified{};
		activePlayer->decideThrow();
		activePlayer->throwDart();
		verified = verifyScore(activePlayer);

		if (verified == ThrowVerification::WIN)
		{
			activePlayer->applyThrowScore();
			// player won the game
			activePlayer->incrementGamesWon();
			return;
		}
		else if (verified == ThrowVerification::INVALID)
		{
			// invalid throw, break to switch player
			break;
		}
		else
		{
			activePlayer->applyThrowScore();
		}
	}

	// switch active player
	players.ToPlay = (players.ToPlay == GamePlayers::ToPlay::PLAYER_ONE) ? GamePlayers::ToPlay::PLAYER_TWO : GamePlayers::ToPlay::PLAYER_ONE;
	activePlayer = { players.arr_players[(int)players.ToPlay] };
}

void Darts::DartGame::displayAccuracies()
{
    //std::cout << players.playerOne.getName() << " has an average accuracy of " << round(p->getTotalAccuracy()) << '\n';
    //std::cout << players.playerTwo.getName() << " has an average accuracy of " << round(p->getTotalAccuracy()) << '\n';
}

// verifies the score, and returns the result
Darts::DartGame::ThrowVerification Darts::DartGame::verifyScore(Player* p)
{

	if (p->getChosenThrow().throwType == &Player::throwDouble)
	{
		if (p->getScore() - p->getThrowScore() == 0)
		{
			return ThrowVerification::WIN;
		}
		else if (p->getScore() - p->getThrowScore() < 2)
		{
			return ThrowVerification::INVALID;
		}
		else
		{
			return ThrowVerification::VALID;
		}
	}

	if (p->getChosenThrow().throwType == &Player::throwBull)
	{
		if (p->getScore() - p->getThrowScore() == 0)
		{
			return ThrowVerification::WIN;
		}
		else if (p->getScore() - p->getThrowScore() < 2)
		{
			return ThrowVerification::INVALID;
		}
		else
		{
			return ThrowVerification::VALID;
		}
	}

	if (p->getScore() - p->getThrowScore() < 2)
	{
		return ThrowVerification::INVALID;
	}
	else
	{
		return ThrowVerification::VALID;
	}

}