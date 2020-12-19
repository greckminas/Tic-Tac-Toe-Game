#include "TicTacGame.h"

int main(){
	TTT::CreateGame(5,false); //buat tabel, dan ukurannya
	TTT::SetUsername(1,"Greck");
	while(1){
		system("cls");
		int a,x,y;
		TTT::PrintGame(); //nampilin tabel
		printf("input untuk %s di x,y = ",TTT::GetUsername(1));
		scanf("%d,%d",&x,&y);
		TTT::DrawTable(1,x,y); //gambar X atau O di posisi (x,y)
	}
	return 0;
}