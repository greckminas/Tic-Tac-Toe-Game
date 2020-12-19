#include "TicTacGame.h"

namespace TTT{
	
	struct Data{
		int Size;
		int WinLen;
		int Difficulty;
		struct Player{
			char name[255];
			bool isBot;
		}Player1,Player2;
		int** Table;
	}Game;

	int CreateGame(int size,bool versus_bot){
		Game.WinLen = 5;
		switch(size){
		case 3:
			Game.WinLen--;
		case 5:
			Game.WinLen--;
		case 7:
			{
			int** table = new int*[size];
			for(int i = 0; i < size; ++i)
				table[i] = new int[size];
			Game.Table = table;
			Game.Size = size;
			for(int i = 0; i < size; i++)
				for(int j = 0; j < size; j++)
					Game.Table[i][j] = 0;
			break;
			}
			
		default:
			return 1; //abnormal size
		}
		Game.Player1.isBot = false;
		Game.Player2.isBot = (versus_bot) ? true : false;
		if(versus_bot){
			strcpy_s(Game.Player2.name,"Bot");

		}
		return 0; //nothing error
	}
	int SetUsername(int num_player, char* name){
		switch(num_player){
		case 1:
			strcpy_s(Game.Player1.name,name);
			break;
		case 2:
			if(Game.Player2.isBot)
				return 2; //player 2 is bot
			else
				strcpy_s(Game.Player2.name,name);
			break;
		default:
			return 1; //abnormal num_player
		}
		return 0; //nothing error
	}
	char* GetUsername(int num_player){
		switch(num_player){
		case 1:
			return Game.Player1.name;
		case 2:
			return Game.Player2.name;
		default:
			return '\0'; //abnormal num_player
		}
	}
	int DrawTable(int player, int x, int y){
		if(Game.Table[y-1][x-1])
			return 3; //the cell is occupied
		if(Game.Size < x || Game.Size < y || x < 1 || y < 1)
			return 2; //x/y out of range

		switch(player){
		case 1:
			Game.Table[y-1][x-1] = 1;
			break;
		case 2:
			Game.Table[y-1][x-1] = 2;
			break;
		default:
			return 1; //abnormal num_player
		}
		return 0;
	}
	void PrintGame(){
		printf("  ");
		for(int i=1;i<=Game.Size;i++)
			printf("%d ",i);					//  1 2 3 4 5
		printf("\n  ");
		for(int i=1;i<=Game.Size;i++)
			printf("- ");						// ----------
		printf("\n");
		for(int y = 0;y<Game.Size;y++){
			printf("%c|",y+'a');
			for(int x = 0;x<Game.Size;x++){
				char temp;
				if(!Game.Table[y][x])
					temp = ' ';
				else if(Game.Table[y][x] == 1)
					temp = 'O';
				else if(Game.Table[y][x] == 2)
					temp = 'X';
				printf("%c|",temp);				//a|X|O|X|O|X|
			}
			printf("\n  ");
			for(int i=1;i<=Game.Size;i++)
				printf("- ");					// ----------
			printf("\n");
		}

	}
}