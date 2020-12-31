#include "TicTacGame.h"

namespace TTT{
	
	struct Data{
		int Size;
		int WinLen;
		int Difficulty;
		int CountTurn;
		bool isTimeout;
		struct Player{
			char name[255];
			bool isBot;
			struct Move{
				int x;
				int y;
			}LastMove;
		}Player1,Player2;
		int** Table;
	};
	Data Game;
	//ascii code
	//0xC4 = -

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
		Game.CountTurn = 0;
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
		SetTimeout(false);
		Game.CountTurn++;
		return 0;
	}

	void PrintGame(){
		system("cls");
		printf("  ");
		for(int i=1;i<=Game.Size;i++)
			printf("%d ",i);					//  1 2 3 4 5

		printf("\n \xda");
		for(int i=1;i<=Game.Size-1;i++)
			printf("\xc4\xc2");
		printf("\xc4\xbf");

		printf("\n");
		for(int y = 0;y<Game.Size;y++){
			printf("%c\xb3",y+'a');
			for(int x = 0;x<Game.Size;x++){
				char temp;
				if(!Game.Table[y][x])
					temp = ' ';
				else if(Game.Table[y][x] == 1)
					temp = 'X';
				else if(Game.Table[y][x] == 2)
					temp = 'O';
				printf("%c\xb3",temp);				//a|X|O|X|O|X|
			}

			printf((y<Game.Size-1) ? "\n \xc3" : "\n \xc0");
			for(int i=1;i<=Game.Size;i++){
				printf((i==Game.Size) ? ((y<Game.Size-1) ? "\xc4\xb4" : "\xc4\xd9") : ((y<Game.Size-1) ? "\xc4\xc5" : "\xc4\xc1"));
			}
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
			if(Game.Table[2][0] == Game.Table[1][1] && Game.Table[0][2] == Game.Table[1][1])
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
		switch(num_player){
		case 1:
			if(!Game.Player1.LastMove.x || !Game.Player1.LastMove.y)
				return 2;
			*x = Game.Player1.LastMove.x;
			*y = Game.Player1.LastMove.y;
			return 0;
		case 2:
			if(!Game.Player2.LastMove.x || !Game.Player2.LastMove.y)
				return 2;
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
		return 0;
	}
	int GetCountTurn(){
		return Game.CountTurn;
	}
	void SetTimeout(bool timeout){
		Game.isTimeout = timeout;
	}
	bool GetTimeout(){
		return Game.isTimeout;
	}
	bool DrawRandom(int num_player){
		if(num_player != 1 && num_player != 2)
			return false; //error

		srand((unsigned int)time(NULL));
		while(1){
			int x_rand = rand() % Game.Size;
			int y_rand = rand() % Game.Size;
			if(!Game.Table[y_rand][x_rand]){
				DrawTable(num_player,x_rand+1,y_rand+1);
				break;
			}
		}
		return true;
	}
	bool SetDifficulty(int level){
		if(level <= 0 || level > 5)
			return false;

		Game.Difficulty = level;
		return true;
	}
}

namespace BOT{

	struct Data{
		int Size;
		int WinLen;
		int** isEmpty;
		int** Table;
		int** WinTable;
		int countEmpty;
		struct point{
			int x;
			int y;
		}BestMove,move_now;
		int BestScore;
	}board;

	void initBot(){
		int** table = new int*[TTT::Game.Size];
		int** table1 = new int*[TTT::Game.Size];
		int** table2 = new int*[TTT::Game.Size];
		for(int i = 0; i < TTT::Game.Size; ++i){
			table[i] = new int[TTT::Game.Size];
			table1[i] = new int[TTT::Game.Size];
			table2[i] = new int[TTT::Game.Size];
		}
		board.isEmpty = table;
		board.Table = table1;
		board.WinTable = table2;
		board.Size = TTT::Game.Size;
		board.WinLen = TTT::Game.WinLen;
		if(!TTT::Game.Difficulty)
			TTT::Game.Difficulty = 1;
	}
	int CheckWinner(BOT::Data board){
		switch(board.Size){
		case 3:
		{
			// check "\"
			if(board.Table[0][0] == board.Table[1][1] && board.Table[1][1] == board.Table[2][2])
				if(board.Table[1][1])
					return board.Table[1][1];

			// check "/"
			if(board.Table[2][0] == board.Table[1][1] && board.Table[0][2] == board.Table[1][1])
				if(board.Table[1][1])
					return board.Table[1][1];

			// check "|"
			for(int i=0;i<board.Size;i++)
				if(board.Table[0][i] == board.Table[1][i] && board.Table[1][i] == board.Table[2][i])
					if(board.Table[1][i])
						return board.Table[1][i];

			// check "-"
			for(int i=0;i<board.Size;i++)
				if(board.Table[i][1] == board.Table[i][0] && board.Table[i][1] == board.Table[i][2])
					if(board.Table[i][1])
						return board.Table[i][1];
			break;
		}
		case 5:
		case 7:
		{
			// check "\"
			for(int y = 0 ; y<=board.Size-board.WinLen ; y++){
				for(int x = 0 ; x<=board.Size-board.WinLen ; x++){
					int beingChecked = board.Table[y][x];
					for(int i = 0; i<board.WinLen; i++)
						if(board.Table[y+i][x+i] != beingChecked)
							beingChecked = 0;
					if(beingChecked)
						return beingChecked;
				}
			}

			// check "/"
			for(int y = 0 ; y<=board.Size-board.WinLen ; y++){
				for(int x = board.Size-1 ; x>=board.WinLen-1 ; x--){
					int beingChecked = board.Table[y][x];
					for(int i = 0; i<board.WinLen; i++)
						if(board.Table[y+i][x-i] != beingChecked)
							beingChecked = 0;
					if(beingChecked)
						return beingChecked;
				}
			}

			// check "|"
			for(int y = 0 ; y<=board.Size-board.WinLen ; y++){
				for(int x = 0 ; x<board.Size ; x++){
					int beingChecked = board.Table[y][x];
					for(int i = 0; i<board.WinLen; i++)
						if(board.Table[y+i][x] != beingChecked)
							beingChecked = 0;
					if(beingChecked)
						return beingChecked;
				}
			}

			// check "-"
			for(int y = 0 ; y<board.Size ; y++){
				for(int x = 0 ; x<=board.Size-board.WinLen ; x++){
					int beingChecked = board.Table[y][x];
					for(int i = 0; i<board.WinLen; i++)
						if(board.Table[y][x+i] != beingChecked)
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
	int GetBestMove(BOT::Data &board, int num_player, int steps){
		
		for(int y = 0; y<board.Size; y++){
			for(int x = 0; x<board.Size; x++){
				if(board.isEmpty[y][x] == 1){
					board.Table[y][x] = num_player;
					board.isEmpty[y][x] = 2;
					int Winner = CheckWinner(board);

					if(Winner==num_player){
						int score = steps*board.Size*board.Size;
						if(!board.WinTable[y][x] || board.WinTable[y][x] > score){
							board.WinTable[y][x] = score;
						} 
					} else {
						if (steps <= TTT::Game.Difficulty && !TTT::GetTimeout()){
							int res = GetBestMove(board,(num_player==1) ? 2 : 1,steps+1); 
						}
					}

					board.Table[y][x] = 0;
					board.isEmpty[y][x] = 1;
				}
			}
		}
		return 0;
	}
	int GetMoveBot(){
		board.BestScore = -1;
		board.countEmpty = 0;
		for(int i = 0; i<board.Size; i++){
			for(int j = 0; j<board.Size; j++){
				if(!TTT::Game.Table[j][i]){
					board.countEmpty++;
				}
			}
		}
		
		for(int y = 0; y<board.Size; y++){
			for(int x = 0; x<board.Size; x++){
				board.Table[y][x] = TTT::Game.Table[y][x];
				board.isEmpty[y][x] = 0;
				board.WinTable[y][x] = 0;
			}
		}
		
		for(int i = 0; i<board.Size; i++){
			for(int j = 0; j<board.Size; j++){
				if(!board.Table[j][i] && board.isEmpty[j][i] != 2){
					board.isEmpty[j][i] = 1;
				} else {
					board.isEmpty[j][i] = 0;
					board.WinTable[j][i] = 0x7FFFFFFF;
				}
			}
		}
	
		GetBestMove(board,2,1);
			
		srand((unsigned int)time(NULL));
		int MinScore = 0x7FFFFFFF;
		for(int y = 0; y<board.Size; y++){
			for(int x = 0; x<board.Size; x++){
				//printf("%016d ",board.WinTable[y][x]);
				if(MinScore > board.WinTable[y][x] && board.WinTable[y][x]){
					MinScore = board.WinTable[y][x];
				}
			}
			//printf("\n");
		}
		if(MinScore == 0x7FFFFFFF)
			MinScore = 0;

		//printf("\n%016d\n",MinScore);
		//system("pause");

		while(1){
			int x_rand = rand() % board.Size;
			int y_rand = rand() % board.Size;
			if(board.WinTable[y_rand][x_rand] == MinScore){
				board.BestMove.x = x_rand;
				board.BestMove.y = y_rand;
				break;
			}
		}
		
		
		if(TTT::DrawTable(2,board.BestMove.x+1,board.BestMove.y+1))
			return 1;
		//end of CheckMove
		return 0;

	}

}