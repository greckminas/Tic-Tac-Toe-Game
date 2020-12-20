#include "TicTacGame.h"

void GameMaking(){
	bool vs_bot = false;
	int size = 0;
	char p1[255] = {};
	char p2[255] = {};

	while(1){
		system("cls");
		printf("Selamat Datang di Tic Tac Toe Game Sederhana!\n");
		if(size != 3 && size != 5 && size != 7){
			printf("Pilih ukuran [3/5/7] = ");
			scanf("%d",&size);
			if(size != 3 && size != 5 && size != 7)
				continue;
		} else 
			printf("Pilih ukuran [3/5/7] = %d\n",size);

		printf("Lawan Bot? [y/t] = ");
		
		char temp_bot;
		scanf("%c",&temp_bot);

		if(temp_bot == 'y' || temp_bot == 'Y')
			vs_bot = true;
		else if(temp_bot != 't' && temp_bot != 'T')
			continue;
		break;
	}
	
	printf("Masukkan Nama Player 1 = ");
	scanf("\n%[^\n]%*c",p1);
	TTT::SetUsername(1,p1);
	if(!vs_bot){
		printf("Masukkan Nama Player 2 = ");
		scanf("\n%[^\n]%*c",p2);
		TTT::SetUsername(2,p2);
	}
	TTT::CreateGame(size,vs_bot); //buat tabel, dan ukurannya
}

int main(){
	
	GameMaking();

	while(1){
		int x,y;
		TTT::PrintGame(); //nampilin tabel
		printf("input untuk %s di x,y = ",TTT::GetUsername(1));
		scanf("%d,%d",&x,&y);
		if(TTT::DrawTable(1,x,y)){ //gambar X atau O di posisi (x,y)
			printf("\noccupied");
			system("pause");
		}
		int Winner = TTT::GetWinner();
		if(Winner){
			TTT::PrintGame(); //nampilin tabel
			if(Winner == -1){
				printf("\nThe game is Draw!\n");
				system("pause");
				break;
			}
			printf("\nThe Winner is %s!\n",TTT::GetUsername(Winner));
			system("pause");
			break;
		}
	}
	return 0;
}