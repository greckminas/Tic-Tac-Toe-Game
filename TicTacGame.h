#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>

namespace TTT{
	int CreateGame(int size, bool versus_bot);
	int SetUsername(int num_player, char* name);
	char* GetUsername(int num_player);
	int DrawTable(int player, int x, int y);
	int GetWinner();
	void PrintGame();
	int GetLastMove(int num_player, int* x, int* y);
	bool isPlayerBot(int num_player);
	int GetCountTurn();
	void SetTimeout(bool timeout);
	bool GetTimeout();
	bool DrawRandom(int num_player);
	bool SetDifficulty(int level);
}

namespace BOT{
	void initBot();
	int GetMoveBot();
}