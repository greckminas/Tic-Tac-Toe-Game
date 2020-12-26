#include "TicTacGame.h"

void GameMaking(int* turn){
	bool vs_bot = false;
	int size = 0;
	char p1[255] = {};
	char p2[255] = {};

	while(1){
		system("cls");
		printf("Selamat Datang di Tic Tac Toe Game Sederhana!\n");
		if(size != 3 && size != 5 && size != 7){
			printf("Pilih ukuran [3/5/7] = ");
			scanf_s("%d",&size);
			std::cin.sync();
			if(size != 3 && size != 5 && size != 7)
				continue;
		} else 
			printf("Pilih ukuran [3/5/7] = %d\n",size);

		printf("Lawan Bot? [y/t] = ");
		
		char temp_bot;
		scanf_s("%c",&temp_bot);
		std::cin.sync();
		if(temp_bot == 'y' || temp_bot == 'Y')
			vs_bot = true;
		else if(temp_bot != 't' && temp_bot != 'T')
			continue;
		break;
	}
	
	printf("Masukkan Nama Player 1 = ");
	scanf_s("\n%[^\n]%*c",p1);
	std::cin.sync();
	TTT::SetUsername(1,p1);
	if(!vs_bot){
		printf("Masukkan Nama Player 2 = ");
		scanf_s("\n%[^\n]%*c",p2);
		std::cin.sync();
		TTT::SetUsername(2,p2);
	} else {
		TTT::SetUsername(2,"Bot");
	}
	while(1){
		system("cls");
		printf("Selamat Datang di Tic Tac Toe Game Sederhana!\n");
		printf("Pilih ukuran [3/5/7] = %d\n",size);
		printf("Siapa giliran pertama ?\n1. %s\n2. %s\n[1/2] = ",TTT::GetUsername(1),TTT::GetUsername(2));
		scanf_s("%d",turn);
		std::cin.sync();
		if(*turn != 1 && *turn != 2)
			continue;
		break;

	}
	fflush(stdin);
	TTT::CreateGame(size,vs_bot); //buat tabel, dan ukurannya
}

bool ConvertInput(char* x, char* y){
	if(*x >= 0x30 && *x <= 0x39){
		*x -= 0x30;
		if(*y >= 0x61 && *y <= 0x7A){
			*y -= 0x60;
			return true;
		}
		else if(*y >= 0x41 && *y <= 0x5A){
			*y -= 0x0;
			return true;
		}
	}
	return false;
}

char errorstr[255] = {};

bool GetInput(int num_player){
	char strinput[2];
	printf("%sInput untuk %s = ",errorstr,TTT::GetUsername(num_player));
	errorstr[0] = 0;

	fgets(strinput,3,stdin);
	fflush(stdin);

	if(ConvertInput(&strinput[0],&strinput[1])){
		if(TTT::GetTimeout()){
			TTT::DrawRandom(num_player);
			strcpy_s(errorstr,"Error = Input timeout. Randomize input!\n");
			return true;
		}
		int res_draw = TTT::DrawTable(num_player,strinput[0],strinput[1]);
		switch(res_draw){ //gambar X atau O di posisi (x,y)
		case 2:
			strcpy_s(errorstr,"Error = Out of Table. Try Again!\n");
			return false;
		case 3:
			strcpy_s(errorstr,"Error = Table is occupied. Try Again!\n");
			return false;
		}
	}
	else {
		strcpy_s(errorstr,"Error = Invalid Input. Try Again!\n");
		return false;
	}
	return true;
}

DWORD WINAPI waitthread(LPVOID){
	int sec = 0;
	int prevturn = 0;
	while(1){
		
		Sleep(1000);
		if(TTT::GetCountTurn() == prevturn)
			sec++;
		else
			sec = 0;
		
		prevturn = TTT::GetCountTurn();

		if(sec >= 10)
			TTT::SetTimeout(true);
	}
	return 0;
}

int main(){
	int turn = 0;
	GameMaking(&turn);
	BOT::initBot();
	CreateThread(0,0,waitthread,0,0,0);
	while(1){
	
		TTT::PrintGame(); //nampilin tabel
				
		if(turn == 1){
			if(GetInput(turn))
					turn = 2;
		}else if(turn == 2){
			if(TTT::isPlayerBot(2))
				while(BOT::GetMoveBot());
			else
				while(!GetInput(turn));
			turn = 1;
		}

		int Winner = TTT::GetWinner();
		if(Winner){
			TTT::PrintGame(); //nampilin tabel
			if(Winner == 3){
				printf("\nThe game is Draw!\n");
				system("pause");
				break;
			}
			printf("\nThe Winner is %s!\n",TTT::GetUsername(Winner));
			system("pause");
			break;
		}
	}
	system("pause");
	system("pause");
	return 0;
}