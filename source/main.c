/*
 * Pxls3DS by Ent1ty & Ske
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <3ds.h>
#include <unistd.h>
#include <sf2d.h>

char pxlsEndpoint[] = "http://pxls.space"; // Pxls endpoint
char* pxlsApi[1] = {
	"/boarddata"
}; // Api endpoints

int boardInfo[3] = {
	1999,
	1999,
	2000
}; // X, Y, Width of board
char *boardColors[16] = {
	"FFFFFF",
	"E4E4E4",
	"888888",
	"222222",
	"FFA7D1",
	"E50000",
	"E59500",
	"A06A42",
	"E5D900",
	"94E044",
	"02BE01",
	"00D3DD",
	"0083C7",
	"0000EA",
	"CF6EE4",
	"820080"
}; // Board colors (in hex)

//boardData.board[boardInfo[1]+boardInfo[2]*boardInfo[3]] ?

struct boardData {
	unsigned char *board;
};

const unsigned int BOARD_SIZE = 4u<<20;

int drawBoard()
{
	struct boardData board;
	board.board = linearAlloc(BOARD_SIZE);

	FILE *fpr = fopen("boarddata", "r");
	if(fpr != NULL)
	{
		fread(board.board, 1, BOARD_SIZE, fpr);
		//printf("%d\n", boardColors[board.board[0+0*2000]]);
		// fclose(fpr);
	}

	int x;
	int y;

	int r, g, b;

	for (x = 0; x < 2000; x++) {
		for (y = 0; y < 2000; y++) {
			sscanf(boardColors[board.board[x+y*2000]], "%02x%02x%02x", &r, &g, &b);
			sf2d_draw_rectangle(x, y, 1, 1, RGBA8(0x00, r, g, b));
		}
	}

	fclose(fpr);
	return 0;
}

int main()
{
	srand(time(NULL));

	sf2d_init();
	sf2d_set_clear_color(RGBA8(0xFF, 0xFF, 0xFF, 0xFF));
	sf2d_set_3D(0);

	while (aptMainLoop())
	{
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			//sf2d_draw_rectangle(5, 5, 1, 1, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
			drawBoard();
		sf2d_end_frame();

		sf2d_swapbuffers();
	}

	sf2d_fini();
	return 0;
}
