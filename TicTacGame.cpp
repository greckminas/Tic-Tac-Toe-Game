#include "TicTacGame.h"

namespace TTT{
	
	struct Data{
		int Size;
		int WinLen;
		int Difficulty;
		struct Player{
			char name[255];
			bool isBot;
			struct Move{
				int x;
				int y;
			}LastMove;
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
		
		if(x > Game.Size || y > Game.Size || x < 1 || y < 1)
			return 2; //x/y out of range

		if(Game.Table[y-1][x-1])
			return 3; //the cell is occupied

		switch(player){
		case 1:
			Game.Player1.LastMove.x = x;
			Game.Player1.LastMove.y = y;
			Game.Table[y-1][x-1] = 1;
			break;
		case 2:
			Game.Player2.LastMove.x = x;
			Game.Player2.LastMove.y = y;
			Game.Table[y-1][x-1] = 2;
			break;
		default:
			return 1; //abnormal num_player
		}
		return 0;
	}
	void PrintGame(){
		system("cls");
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
					temp = 'X';
				else if(Game.Table[y][x] == 2)
					temp = 'O';
				printf("%c|",temp);				//a|X|O|X|O|X|
			}
			printf("\n  ");
			for(int i=1;i<=Game.Size;i++)
				printf("- ");					// ----------
			printf("\n");
		}

	}
	int GetWinner(){
		int Winner = -1; //-1 is equal as draw
		for(int i = 0;i<Game.Size;i++)
			for(int j = 0;j<Game.Size;j++)
				if(!Game.Table[i][j]){
					Winner = 0;
					break;
				}

		if(Winner == -1)
			return 3; //draw

		switch(Game.Size){
		case 3:
		{
			// check "\"
			if(Game.Table[0][0] == Game.Table[1][1] && Game.Table[1][1] == Game.Table[2][2])
				if(Game.Table[1][1])
					return Game.Table[1][1];

			// check "/"
			if(Game.Table[2][0] == Game.Table[1][1] && Game.Table[2][0] == Game.Table[1][1])
				if(Game.Table[1][1])
					return Game.Table[1][1];

			// check "|"
			for(int i=0;i<Game.Size;i++)
				if(Game.Table[0][i] == Game.Table[1][i] && Game.Table[1][i] == Game.Table[2][i])
					if(Game.Table[1][i])
						return Game.Table[1][i];

			// check "-"
			for(int i=0;i<Game.Size;i++)
				if(Game.Table[i][1] == Game.Table[i][0] && Game.Table[i][1] == Game.Table[i][2])
					if(Game.Table[i][1])
						return Game.Table[i][1];
			break;
		}
		case 5:
		case 7:
		{
			// check "\"
			for(int y = 0 ; y<=Game.Size-Game.WinLen ; y++){
				for(int x = 0 ; x<=Game.Size-Game.WinLen ; x++){
					int beingChecked = Game.Table[y][x];
					for(int i = 0; i<Game.WinLen; i++)
						if(Game.Table[y+i][x+i] != beingChecked)
							beingChecked = 0;
					if(beingChecked)
						return beingChecked;
				}
			}

			// check "/"
			for(int y = 0 ; y<=Game.Size-Game.WinLen ; y++){
				for(int x = Game.Size-1 ; x>=Game.WinLen-1 ; x--){
					int beingChecked = Game.Table[y][x];
					for(int i = 0; i<Game.WinLen; i++)
						if(Game.Table[y+i][x-i] != beingChecked)
							beingChecked = 0;
					if(beingChecked)
						return beingChecked;
				}
			}

			// check "|"
			for(int y = 0 ; y<=Game.Size-Game.WinLen ; y++){
				for(int x = 0 ; x<Game.Size ; x++){
					int beingChecked = Game.Table[y][x];
					for(int i = 0; i<Game.WinLen; i++)
						if(Game.Table[y+i][x] != beingChecked)
							beingChecked = 0;
					if(beingChecked)
						return beingChecked;
				}
			}

			// check "-"
			for(int y = 0 ; y<Game.Size ; y++){
				for(int x = 0 ; x<=Game.Size-Game.WinLen ; x++){
					int beingChecked = Game.Table[y][x];
					for(int i = 0; i<Game.WinLen; i++)
						if(Game.Table[y][x+i] != beingChecked)
							beingChecked = 0;
					if(beingChecked)
						return beingChecked;
				}
			}
			break;
		}
		}
		return 0;
	}
	int GetLastMove(int num_player, int* x, int* y){
		if(!*x || !*y)
			return 2; //invalid move
		switch(num_player){
		case 1:
			*x = Game.Player1.LastMove.x;
			*y = Game.Player1.LastMove.y;
			return 0;
		case 2:
			*x = Game.Player2.LastMove.x;
			*y = Game.Player2.LastMove.y;
			return 0;
		default:
			return 1;//abnormal num_player
		}
	}
	bool isPlayerBot(int num_player){
		switch(num_player){
		case 1:
			return Game.Player1.isBot;
		case 2:
			return Game.Player2.isBot;
		}
	}
}