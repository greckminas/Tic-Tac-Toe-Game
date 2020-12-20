#include <stdio.h>
#include <string>

namespace TTT{
	int CreateGame(int size, bool versus_bot);
	int SetUsername(int num_player, char* name);
	char* GetUsername(int num_player);
	int DrawTable(int player, int x, int y);
	int GetWinner();
	void PrintGame();
}