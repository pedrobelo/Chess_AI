#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <time.h>
#include "interface.h"
#include "rules.h"

#define SQ_SIZE 60

char game_mode(int mode)
{
	char board[8][8];
	int castling[2][2] = {{1,1},{1,1}};
	int en_passant = -1;
	//int cnt=0;
	bool quit = false;

	srand(time(NULL));

	if(1)
	{
		board[0][0] = 'R'; board[0][1] = 'N'; board[0][2] = 'B'; board[0][3] = 'Q'; board[0][4] = 'K'; board[0][5] = 'B'; board[0][6] = 'N'; board[0][7] = 'R';
		board[1][0] = 'P'; board[1][1] = 'P'; board[1][2] = 'P'; board[1][3] = 'P'; board[1][4] = 'P'; board[1][5] = 'P'; board[1][6] = 'P'; board[1][7] = 'P';
		board[2][0] = '_'; board[2][1] = '_'; board[2][2] = '_'; board[2][3] = '_'; board[2][4] = '_'; board[2][5] = '_'; board[2][6] = '_'; board[2][7] = '_';
		board[3][0] = '_'; board[3][1] = '_'; board[3][2] = '_'; board[3][3] = '_'; board[3][4] = '_'; board[3][5] = '_'; board[3][6] = '_'; board[3][7] = '_';
		board[4][0] = '_'; board[4][1] = '_'; board[4][2] = '_'; board[4][3] = '_'; board[4][4] = '_'; board[4][5] = '_'; board[4][6] = '_'; board[4][7] = '_';
		board[5][0] = '_'; board[5][1] = '_'; board[5][2] = '_'; board[5][3] = '_'; board[5][4] = '_'; board[5][5] = '_'; board[5][6] = '_'; board[5][7] = '_';
		board[6][0] = 'p'; board[6][1] = 'p'; board[6][2] = 'p'; board[6][3] = 'p'; board[6][4] = 'p'; board[6][5] = 'p'; board[6][6] = 'p'; board[6][7] = 'p';
		board[7][0] = 'r'; board[7][1] = 'n'; board[7][2] = 'b'; board[7][3] = 'q'; board[7][4] = 'k'; board[7][5] = 'b'; board[7][6] = 'n'; board[7][7] = 'r';
	}
	else
	{
		board[0][0] = 'R'; board[0][1] = 'N'; board[0][2] = 'B'; board[0][3] = 'Q'; board[0][4] = 'K'; board[0][5] = '_'; board[0][6] = '_'; board[0][7] = 'R';
		board[1][0] = 'P'; board[1][1] = 'P'; board[1][2] = 'P'; board[1][3] = 'P'; board[1][4] = '_'; board[1][5] = 'P'; board[1][6] = 'P'; board[1][7] = 'P';
		board[2][0] = '_'; board[2][1] = '_'; board[2][2] = '_'; board[2][3] = '_'; board[2][4] = '_'; board[2][5] = 'N'; board[2][6] = '_'; board[2][7] = '_';
		board[3][0] = '_'; board[3][1] = '_'; board[3][2] = 'B'; board[3][3] = '_'; board[3][4] = 'P'; board[3][5] = '_'; board[3][6] = '_'; board[3][7] = '_';
		board[4][0] = '_'; board[4][1] = '_'; board[4][2] = 'b'; board[4][3] = '_'; board[4][4] = 'p'; board[4][5] = '_'; board[4][6] = '_'; board[4][7] = '_';
		board[5][0] = '_'; board[5][1] = '_'; board[5][2] = '_'; board[5][3] = '_'; board[5][4] = '_'; board[5][5] = 'n'; board[5][6] = '_'; board[5][7] = '_';
		board[6][0] = 'p'; board[6][1] = 'p'; board[6][2] = 'p'; board[6][3] = 'p'; board[6][4] = '_'; board[6][5] = 'p'; board[6][6] = 'p'; board[6][7] = 'p';
		board[7][0] = 'r'; board[7][1] = '_'; board[7][2] = '_'; board[7][3] = '_'; board[7][4] = 'k'; board[7][5] = '_'; board[7][6] = '_'; board[7][7] = 'r';
	}

	if(mode == 1)//person vs person
	{
		int check_val=0;
		SDL_Window *window;
		SDL_Renderer* renderer;
		SDL_Texture * sprite;

		initialization();
		window = open_window(SQ_SIZE);
		renderer = create_renderer(window);
		sprite = create_sprite(renderer);

		while(check_val < 2 && !quit)
		{	
			check_val = check(board, 'w', &en_passant, castling);
			//printf("%d\n", check_val);
			if(check_val == 2)
				return '_';
			else if(check_val == 3)
				return 'b';

			manage_moves(renderer, sprite, board, SQ_SIZE, piece_move, &en_passant, castling, 'w', &quit);

			check_val = check(board, 'b', &en_passant, castling);
			//printf("%d\n", check_val);
			if(check_val == 2)
				return '_';
			else if(check_val == 3)
				return 'w';

			manage_moves(renderer, sprite, board, SQ_SIZE, piece_move, &en_passant, castling, 'b', &quit);
		}
		destroy(window, renderer);
	}
/*	else if(mode == 2)//person vs pc(person plays black)
	{
		initialization();
		window = open_window(sq_size);
		renderer = create_renderer(window);
		sprite = create_sprite(renderer);

		while(check_val < 2 && !quit)
		{	
			check_val = check(board, 'w', &en_passant);
			if(check_val == 2)
				return '_';
			else if(check_val == 3)
				return 'b';

			brain(board, en_passant, castling, 'w', x_i, y_i, x_f, y_f);
			piece_move(board, 'w', x_i, y_i, x_f, y_f, &en_passant, upgrade, castling);

			check_val = check(board, 'b', &en_passant);
			if(check_val == 2)
				return '_';
			else if(check_val == 3)
				return 'w';

			manage_moves(renderer, sprite, board, 60, NULL, &en_passant, castling, 'b');
		}
		destroy(window, renderer);
	}
	else if(mode == 3)//person vs pc(peron plays white)
	{
		initialization();
		window = open_window(sq_size);
		renderer = create_renderer(window);
		sprite = create_sprite(renderer);

		while(check_val < 2 && !quit)
		{	
			check_val = check(board, 'w', &en_passant);
			if(check_val == 2)
				return '_';
			else if(check_val == 3)
				return 'b';

			manage_moves(renderer, sprite, board, 60, NULL, &en_passant, castling, 'w');

			check_val = check(board, 'b', &en_passant);
			if(check_val == 2)
				return '_';
			else if(check_val == 3)
				return 'w';

			brain(board, en_passant, castling, 'b', x_i, y_i, x_f, y_f);
			piece_move(board, 'b', x_i, y_i, x_f, y_f, &en_passant, upgrade, castling);
		}
		destroy(window, renderer);
	}
	else if(mode = 4)//pc vs pc
	{
		while(cnt < 150)
		{
			check_val = check(board, 'w', &en_passant);
			if(check_val == 2)
				return '_';
			else if(check_val == 3)
				return 'b';

			brain(board, en_passant, castling, 'w', x_i, y_i, x_f, y_f);
			piece_move(board, 'w', x_i, y_i, x_f, y_f, &en_passant, upgrade, castling);

			check_val = check(board, 'b', &en_passant);
			if(check_val == 2)
				return '_';
			else if(check_val == 3)
				return 'w';

			brain(board, en_passant, castling, 'b', x_i, y_i, x_f, y_f);
			piece_move(board, 'b', x_i, y_i, x_f, y_f, &en_passant, upgrade, castling);

			cnt++;
		}
	}
	*/
	return 'e';
}