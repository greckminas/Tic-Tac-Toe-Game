#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>

namespace TTT{
	int CreateGame(int size, bool versus_bot); /* Inisialisasi permainan */
	int SetUsername(int num_player, char* name); /* Mengatur nama pemain */
	char* GetUsername(int num_player); /* Mendapatkan nama pemain */
	int DrawTable(int player, int x, int y); /* Menempatkan bidak ke dalam papan */
	int GetWinner(); /* Menampilkan papan */
	void PrintGame(); /* Mendapatkan pemenang */
	int GetLastMove(int num_player, int* x, int* y); /* Mendapatkan letak bidak terakhir yang disimpan */
	bool isPlayerBot(int num_player); /* Mengetahui apakah pemain tersebut merupakan bot atau bukan */
	int GetCountTurn(); /* Mendapatkan jumlah giliran */
	void SetTimeout(bool timeout); /* Menetapkan timeout player */
	bool GetTimeout(); /* Mendapatkan status timeout */
	bool DrawRandom(int num_player); /* Menempatkan bidak ke dalam papan SECARA ACAK */
	bool SetDifficulty(int level); /* Menetapkan tingkat kesulitan */
}

namespace BOT{
	void initBot(); /* Inisialisasi bot*/
	int GetMoveBot(); /* Melakukan pergerakan komputer */
}

namespace File{
	int Save(int Winner); /* Menyimpan record ke dalam file*/
	int Read(); /* Membaca record pada suatu file*/
}