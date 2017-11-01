/*******************************************************
** CHESS_AI
**
** File: interface.c
**
** Ojective: manage visual interface for user
**
** Done by:
**		Pedro Belo
**
** Last modification:
**		17/7/2017
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define WIDTH 640
#define HEIGHT 480


bool initialization()
{
	//SDL_INIT_VIDEO_ is a flag. initializes video and events 
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL not initialized correctly: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

SDL_Window* open_window(int sq_size)
{
	SDL_Window *window;

	//Arguments: Title of the window; x; y; width; height; no specific flags
	window = SDL_CreateWindow("Chess_AI", 100, 100, sq_size*10, sq_size*8, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		printf("Window not opened correctly: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	return window;
}

SDL_Renderer* create_renderer(SDL_Window *window)
{
	SDL_Renderer *renderer;
	//flags: uses hardware acceleration and is synchronized with refresh rate
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL)
	{
		printf("Renderer could not be created: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	return renderer;
}

void destroy(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Texture * create_sprite(SDL_Renderer *renderer)
{
	SDL_Surface *sprite;
	SDL_Surface *surface;
	SDL_Rect pos;
	Uint32 rmask, gmask, bmask, amask;


	/*
	p 	  | P
	b 	  | B
	n 	  | N
	r 	  | R
	q 	  | Q
	k 	  | K
	white | black
	*/

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif


	surface = SDL_CreateRGBSurface(0, 300, 300, 32, rmask, gmask, bmask, amask);
	sprite = SDL_CreateRGBSurface(0, 600, 2100, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(sprite, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

	pos.x = 0; pos.y = 1800; pos.w = 300; pos.h = 300;
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 255, 255));
	SDL_BlitSurface(surface, NULL, sprite, &pos);

	pos.x = 300; pos.y = 1800; pos.w = 300; pos.h = 300;
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 118, 150, 86, 255));
	SDL_BlitSurface(surface, NULL, sprite, &pos);

	SDL_FreeSurface(surface);

	pos.x = 0; pos.y = 0; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/w_pawn.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly1\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 300; pos.y = 0; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/b_pawn.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly2\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 0; pos.y = 300; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/w_bishop.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly3\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 300; pos.y = 300; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/b_bishop.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly4\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 0; pos.y = 600; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/w_knight.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly5\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 300; pos.y = 600; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/b_knight.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly6\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 0; pos.y = 900; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/w_rook.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly7\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 300; pos.y = 900; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/b_rook.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly8\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 0; pos.y = 1200; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/w_queen.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly9\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 300; pos.y = 1200; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/b_queen.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly10\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 0; pos.y = 1500; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/w_king.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly11\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	pos.x = 300; pos.y = 1500; pos.w = 300; pos.h = 300;
	surface = IMG_Load("/home/belo/Desktop/Chess_AI/images/b_king.png");
	if(surface == NULL)
	{
		printf("image not loaded correctly12\n");
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(surface, NULL, sprite, &pos);
	SDL_FreeSurface(surface);

	return SDL_CreateTextureFromSurface(renderer, sprite);
}

void print_piece(SDL_Renderer *renderer, SDL_Texture *sprite, int sq_size, char piece, int x, int y)
{
	SDL_Rect dest, src;
	if(piece == 'p')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 0; src.y = 0; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'P')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 300; src.y = 0; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'b')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 0; src.y = 300; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'B')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 300; src.y = 300; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'n')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 0; src.y = 600; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'N')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 300; src.y = 600; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'r')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 0; src.y = 900; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'R')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 300; src.y = 900; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'q')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 0; src.y = 1200; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'Q')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 300; src.y = 1200; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'k')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 0; src.y = 1500; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
	else if(piece == 'K')
	{
		dest.x = x; dest.y = y; dest.w = sq_size; dest.h = sq_size;
		src.x = 300; src.y = 1500; src.w = 300; src.h = 300;
		SDL_RenderCopy(renderer, sprite, &src, &dest);
	}
}

void print_board(SDL_Renderer *renderer, SDL_Texture *sprite, char board[8][8], int sq_size)
{
	int i, j;
	SDL_Rect dest, src;

	//prints the board row by row; j --> x axis; i --> y axis
	for(i=0; i < 8; i++)
	{
		for(j=0; j < 8; j++)
		{
			dest.x = j*sq_size; dest.y = i*sq_size; dest.w = sq_size; dest.h = sq_size;
			if((i+j)%2 == 0)
			{
				src.x = 0; src.y = 1800; src.w = 300; src.h = 300;
			}
			else
			{
				src.x = 300; src.y = 1800; src.w = 300; src.h = 300;
			}

			SDL_RenderCopy(renderer, sprite, &src, &dest);

			print_piece(renderer, sprite, sq_size, board[i][j], j*sq_size, i*sq_size);
		}
	}
}

void check_events(char board[8][8], bool *quit, char *piece, int sq_size, int *xp, int *yp, int *pressed, int *x, int *y)
{
	SDL_Event e;
	char aux;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			*quit = true;
			break;
		}
		
		if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
		{
			*xp = e.button.x;
			*yp = e.button.y;

			*x = (*xp)/sq_size;
			*y = (*yp)/sq_size;
			*piece = board[*y][*x];
			board[*y][*x] = '_';

			*pressed = 1;
		}
		else if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
		{
			*xp = e.button.x;
			*yp = e.button.y;

			*x = (*xp)/sq_size;
			*y = (*yp)/sq_size;
			aux = board[*y][*x];
			board[*y][*x] = *piece;
			*piece = aux;

			*pressed = 2;
		}
	}
	SDL_GetMouseState(xp, yp);

}

void manage_moves(SDL_Renderer *renderer, SDL_Texture *sprite, char board[8][8], int sq_size, int (*move_p)(char [8][8], char, int, int, int, int, int*, int [2][2]), int *en_passant, int castling[2][2], char color, bool *quit)
{
	char piece='_', piece1, piece2;
	int x, y;
	int pressed=0;
	int x_i, y_i, x_f, y_f;
	int validp = 0;
	char upgrade = '0';

	while(!(*quit) && validp != 1)
	{
		SDL_RenderClear(renderer);

		check_events(board, quit, &piece, sq_size, &x, &y, &pressed, &x_f, &y_f);
		if(pressed == 1)
		{
			x_i = x_f;
			y_i = y_f;
			piece1 = piece;
		}
		else if(pressed == 2)
		{
			piece2 = piece;
			if(move_p != NULL)
			{
				board[y_f][x_f] = piece2;
				board[y_i][x_i] = piece1;
				validp = move_p(board, color, x_i, y_i, x_f, y_f, en_passant, castling);
				if(((y_f == 0 && color == 'w') || (y_f == 7 && color == 'b')) && validp == 1)
				{
					printf("Enter your pawn upgrade: ");
					scanf("%c", &upgrade);
					board[y_f][x_f] = upgrade;
				}
			}
			piece = '_';
		}
		pressed = 0;

		print_board(renderer, sprite, board, sq_size);

		print_piece(renderer, sprite, sq_size, piece, x-sq_size/2, y-sq_size/2);

		SDL_RenderPresent(renderer);
	}
}

//pass the function taht evaluates valid moves by ref
/*void manage_chess_interface(char board[8][8], int sq_size, int (*move_p)(char [8][8], int, int, int, int, char, int*, int [2][2]), int *en_passant, int castling[2][2])
{
	SDL_Window *window;
	SDL_Renderer* renderer;
	SDL_Texture * sprite;

	initialization();
	window = open_window(sq_size);
	renderer = create_renderer(window);
	sprite = create_sprite(renderer);
	
	manage_moves(renderer, sprite, board, sq_size, move_p, en_passant, castling);
	destroy(window, renderer);
}*/



