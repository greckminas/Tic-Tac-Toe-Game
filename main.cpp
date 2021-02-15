#include "TicTacGame.h"

void GameMaking(int* turn){
	bool vs_bot = false;
	int level = 0;
	int size = 0;
	char p1[255] = {};
	char p2[255] = {};

	while(1){
		system("cls");
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
		printf("Pilih ukuran [3/5/7] = %d\n",size);
		if(*turn != 1 && *turn != 2){
			printf("Siapa giliran pertama ?\n1. %s\n2. %s\n[1/2] = ",TTT::GetUsername(1),TTT::GetUsername(2));
			scanf_s("%d",turn);
			std::cin.sync();
			if(*turn != 1 && *turn != 2)
				continue;
		}
		else 
			printf("Giliran pertama = %d. %s\n",*turn,TTT::GetUsername(*turn));

		if((level < 1 || level > 5) && vs_bot){
			printf("Tentukan tingkat kesulitan [1-5] = ");
			scanf_s("%d",&level);
			std::cin.sync();
			if(level < 1 || level > 5)
				continue;
		}

		break;

	}
	TTT::SetDifficulty(level);
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
	printf("Input untuk %s = ",TTT::GetUsername(num_player));
	errorstr[0] = 0;

	fgets(strinput,3,stdin);
	fflush(stdin);

	if(ConvertInput(&strinput[0],&strinput[1])){
		if(TTT::GetTimeout()){
			TTT::DrawRandom(num_player);
			strcpy_s(errorstr,"Error = Input terlalu lama. Input diacak!\n");
			return true;
		}
		int res_draw = TTT::DrawTable(num_player,strinput[0],strinput[1]);
		switch(res_draw){ //gambar X atau O di posisi (x,y)
		case 2:
			strcpy_s(errorstr,"Error = Diluar papan. Coba lagi!\n");
			return false;
		case 3:
			strcpy_s(errorstr,"Error = Kotak telah terisi. Coba lagi!\n");
			return false;
		}
	}
	else {
		strcpy_s(errorstr,"Error = Input tidak valid. Coba lagi!\n");
		return false;
	}
	return true;
}

DWORD WINAPI timerthread(LPVOID){
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

DWORD WINAPI winthread(LPVOID param){
	int Winner = *(int*)param;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int color = 8;
	while(1){
		if(++color > 15)
			color = 9;
		SetConsoleTextAttribute(hOut,color);
		TTT::PrintGame(); //tampilkan tabel
			if(Winner == 3){
				printf("\nPermainan berakhir Seri!\n");
			} else {
				printf("\nPemenangnya adalah %s!",TTT::GetUsername(Winner));
			}
			printf("\nTekan ESC Untuk keluar permainan!\nTekan Spasi untuk kembali ke main menu!");
			if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
				exit(0);
			else if(GetAsyncKeyState(VK_SPACE)&0x8000)
				return 0;
			/*
				nilai return GetAsyncKeyState()
				0x8000 = sedang ditekan
				0x1 = transisi antara dilepas dan ditekan
			*/
			Sleep(100);
	}
	return 0;
}

void SetConsole(){
	SetConsoleTitle("Tic Tac Toe");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_MEDIUM;
	*cfi.FaceName = *L"Consolas";
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),false,&cfi);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

void Scoreboard(){
	system("cls");
	printf("Riwayat permainan yang telah menang melawan Bot\n");
	File::Read();
	printf("Tekan tombol apapun untuk kembali ke Main Menu\n");
	_getch();
}

void HowToPlay(){
	system("cls");
	//cara memulai permainan
	printf( "\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n" );
	printf("\xB3%-67s\xB3\n","Cara memulai permainan :");
	printf("\xB3%-67s\xB3\n","1. Pada main menu, tekan ankga [1] untuk mulai bermain");
	printf("\xB3%-67s\xB3\n","2. Pilih ukuran papan permainan, ada 3 pilihan yaitu 3, 5, dan 7");
	printf("\xB3%-67s\xB3\n","3. Tentukan apakah ingin melawan Bot atau tidak");
	printf("\xB3%-67s\xB3\n\xB3%-67s\xB3\n","3.1. Jika tidak melawan bot, maka anda diharuskan memasukkan nama","     pemain pertama dan kedua");
	printf("\xB3%-67s\xB3\n\xB3%-67s\xB3\n","3.2. Jika melawan bot, maka anda hanya memasukkan nama pemain","     pertama");
	printf("\xB3%-67s\xB3\n","4. Tentukan siapa giliran pertamanya");
	printf("\xB3%-67s\xB3\n\xB3%-67s\xB3\n","5. Jika melawan bot, Tentukan juga tingkat kesulitan dari 1 hingga","   5");
	printf( "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n" );
	
	//cara memasukkan bidak
	printf( "\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n" );
	printf("\xB3%-67s\xB3\n","Cara memasukkan bidak :");
	printf("\xB3%-67s\xB3\n\xB3%-67s\xB3\n","Ketik koordinat x (horizontal) terlebih dahulu dilanjutkan","koordinat y (vertikal) tanpa dipisah oleh spasi.");
	printf("\xB3%-67s\xB3\n\xB3%-67s\xB3\n","Contoh : \"1b\", berarti kotak yang dipilih adalah kolom pertama","dan baris kedua");
	printf( "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n" );
	
	//sistem scoreboard
	printf( "\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n" );
	printf("\xB3%-67s\xB3\n","Sistem Scoreboard :");
	printf("\xB3%-67s\xB3\n\xB3%-67s\xB3\n","Scoreboard hanya terisi jika pemain telah memenangkan permainan","melawan Bot saja.");
	printf("\xB3%-67s\xB3\n","Scoreboard hanya menampilkan 10 kemenangan terakhir.");
	printf( "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n" );

	printf( "\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n" );
	printf("\xB3%-67s\xB3\n","Tentang Permainan :");
	printf("\xB3%-67s\xB3\n\xB3%-67s\xB3\n","Permainan ini dibuat dalam bahasa C++ menggunakan compiler", "Microsoft Visual C++ 2010.");
	printf("\xB3%-67s\xB3\n\xB3%-67s\xB3\n","Permainan ini dibuat oleh Gefi Aulia Sanjaya dan Rangga Yudha", "Yudistira.");
	printf( "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n" );	

	printf("Tekan tombol apapun untuk kembali ke Main Menu\n");
	_getch();
}

int MainMenu(){
	/*
		1. Play
		2. Scoreboard
		3. Help
	*/
	while(1){
		int menu = 0;
		system("cls");
		printf("Tic Tac Toe\n");
		printf("1. Mulai bermain\n2. Sang penakluk\n3. Cara bermain\n4. Keluar permainan\n");
		printf("[1/2/3/4] = ");
		scanf_s("%d",&menu);
		std::cin.sync();
		if(menu != 1 && menu != 2 && menu != 3 && menu != 4)
			continue;
		switch(menu){
		case 1:
			return 0; //keluar perulangan dan lanjut bermain
		case 2:
			Scoreboard();
			break;
		case 3:
			HowToPlay();
			break;
		case 4:
			exit(0);
			break;
		}
	}
	return 0;
}

int main(){
	while(1){
		SetConsole();
		MainMenu();
		int turn = 0;
		int x = 0, y = 0;
		GameMaking(&turn);
		BOT::initBot();
		HANDLE hTimer = CreateThread(0,0,timerthread,0,0,0);
		
		while(1){
			
			TTT::PrintGame(); //tampilkan tabel
			printf("%s\n",errorstr);
			/* Menampilkan gerakan terakhir */
			if(!TTT::GetLastMove((turn==1) ? 2 : 1,&x,&y)){
				printf("Move terakhir oleh %s pada titik (%d,%c)\n",TTT::GetUsername((turn==1) ? 2 : 1),x,y+'a'-1);
			}

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
				TerminateThread(hTimer,0);
				int* param = new int(Winner);
				if(TTT::isPlayerBot(2) && Winner == 1){
					File::Save(Winner);
				}
				WaitForSingleObject(CreateThread(0,0,winthread,param,0,0),INFINITE);
				break;
			}
		}
	}
	return 0;
}