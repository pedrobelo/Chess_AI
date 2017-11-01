#include <stdio.h>
#include <stdlib.h>
#include "rules.h"

#define B_SIZE 8

//default function description

/**********************************************************************************************
Function:

Ojective:

Arguments:

Return value:
	
**********************************************************************************************/

/**********************************************************************************************
Function: get_king_pos

Ojective: Searches the entire board for the king of a specific color

Arguments:
	board[][] --> contains the entire board with each pieces position
	color --> color of the king
	*x, *y --> coordinates of the found king

Return value:
	this function doesn't return a value

**********************************************************************************************/
void get_king_pos(char board[8][8], char color, int *x, int *y)
{
	char king;
	int i, j;

	if(color == 'w')
		king = 'k';
	else
		king = 'K';

	for (i = 0; i < B_SIZE; i++)
	{
		for (j = 0; j < B_SIZE; j++)
		{
			if(board[i][j] == king)
			{
				*x = j;
				*y = i;
			}
		}
	}
}

/**********************************************************************************************
Function: threats

Ojective: check if a certain position is currently under attack. This will be used to see if
	the king can move by checking if its adjacent position are under attack. This fuction might
	be used for other similar purposes.

Arguments:
	board[][] --> contains the entire board with each pieces position
	x, y --> coordinates that are to be checked if they are under threat
	color --> color of the attacking player
	*threat_x, *threat_y --> first piece that is found to be attacking the wanted square

Return value:
	returns 1 is the square is in fact under attack, 0 otherwise
	
**********************************************************************************************/
int threats(char board[8][8], int x, int y, char color, int *threat_x, int *threat_y)
{
	int check = 0;
	char pawn, bishop, knight, rook, queen, king;
	int i=0;

	if(color == 'w')
	{
		
		pawn = 'P';
		bishop = 'B';
		knight = 'N';
		rook = 'R';
		queen = 'Q';
		king = 'K';
	}
	else
	{
		pawn = 'p';
		bishop = 'b';
		knight = 'n';
		rook = 'r';
		queen = 'q';
		king = 'k';
	}

	if(color == 'w')
	{
		if(y-1 >= 0)
		{
			if(x+1 < 8 && board[y-1][x+1] == pawn)
			{
				*threat_x = x+1; *threat_y = y-1; 
				check = 1;
			}
			else if(x-1 >= 0 && board[y-1][x-1] == pawn)
			{
				*threat_x = x-1; *threat_y = y-1; 
				check = 1;
			}
		}
	}
	else
	{
		if(y+1 < 8)
		{
			if(x+1 < 8 && board[y+1][x+1] == pawn)
			{
				*threat_x = x+1; *threat_y = y+1; 
				check = 1;
			}
			else if(x-1 >= 0 && board[y+1][x-1] == pawn)
				check = 1;
		}
	}

	if(y+2 < 8)
	{
		if(x+1 < 8 && board[y+2][x+1] == knight)
		{
			*threat_x = x+1; *threat_y = y+2; 
			check = 1;
		}
		if(x-1 >= 0 && board[y+2][x-1] == knight)
		{
			*threat_x = x-1; *threat_y = y+2; 
			check = 1;
		}
	}
	if(y+1 < 8)
	{
		if(x+2 < 8 && board[y+1][x+2] == knight)
		{
			*threat_x = x+2; *threat_y = y+1; 
			check = 1;
		}
		if(x-2 >= 0 && board[y+1][x-2] == knight)
		{
			*threat_x = x-2; *threat_y = y+1; 
			check = 1;
		}
	}
	if(y-1 >= 0)
	{
		if(x+2 < 8 && board[y-1][x+2] == knight)
		{
			*threat_x = x+2; *threat_y = y-1; 
			check = 1;
		}
		if(x-2 >= 0 && board[y-1][x-2] == knight)
		{
			*threat_x = x-2; *threat_y = y-1; 
			check = 1;
		}
	}
	if(y-2 >= 0)
	{
		if(x+1 < 8 && board[y-2][x+1] == knight)
		{
			*threat_x = x+1; *threat_y = y-2; 
			check = 1;
		}
		if(x-1 >= 0 && board[y-2][x-1] == knight)
		{
			*threat_x = x-1; *threat_y = y-2; 
			check = 1;
		}
	}

	if(check != 1)
	{
		for (i = 1; x+i < 8 && y+i < 8; i++)
		{
			if(board[y+i][x+i] != '_')
			{
				if(board[y+i][x+i] == bishop || board[y+i][x+i] == queen || (board[y+i][x+i] == king && i == 1))
				{
					*threat_x = x+i; *threat_y = y+i; 
					check = 1;
				}
				break;
			}
		}
	}
	if(check != 1)
	{
		for (i = 1; x-i >= 0 && y-i >= 0; i++)
		{
			if(board[y-i][x-i] != '_')
			{
				if(board[y-i][x-i] == bishop || board[y-i][x-i] == queen || (board[y-i][x-i] == king && i == 1))
				{
					*threat_x = x-i; *threat_y = y-i; 
					check = 1;
				}
				break;
			}
		}
	}
	if(check != 1)
	{
		for (i = 1; x-i >= 0 && y+i < 8; i++)
		{
			if(board[y+i][x-i] != '_')
			{
				if(board[y+i][x-i] == bishop || board[y+i][x-i] == queen || (board[y+i][x-i] == king && i == 1))
				{
					*threat_x = x-i; *threat_y = y+i; 
					check = 1;
				}
				break;
			}
		}
	}
	if(check != 1)
	{
		for (i = 1; x+i < 8 && y-i >= 0; i++)
		{
			if(board[y-i][x+i] != '_')
			{
				if(board[y-i][x+i] == bishop || board[y-i][x+i] == queen || (board[y-i][x+i] == king && i == 1))
				{
					*threat_x = x+i; *threat_y = y-i; 
					check = 1;
				}
				break;
			}
		}
	}
	if(check != 1)
	{
		for (i = 1; x+i < 8; i++)
		{
			if(board[y][x+i] != '_')
			{
				if(board[y][x+i] == rook || board[y][x+i] == queen || (board[y][x+i] == king && i == 1))
				{
					*threat_x = x+i; *threat_y = y; 
					check = 1;
				}
				break;
			}
		}
	}
	if(check != 1)
	{
		for (i = 1; x-i >= 0; i++)
		{
			if(board[y][x-i] != '_')
			{
				if(board[y][x-i] == rook || board[y][x-i] == queen || (board[y][x-i] == king && i == 1))
				{
					*threat_x = x-i; *threat_y = y; 
					check = 1;
				}
				break;
			}
		}
	}
	if(check != 1)
	{
		for (i = 1; y+i < 8; i++)
		{
			if(board[y+i][x] != '_')
			{
				if(board[y+i][x] == bishop || board[y+i][x] == queen || (board[y+i][x] == king && i == 1))
				{
					*threat_x = x; *threat_y = y+i; 
					check = 1;
				}
				break;
			}
		}
	}
	if(check != 1)
	{
		for (i = 1; y-i >= 0; i++)
		{
			if(board[y-i][x] != '_')
			{
				if(board[y-i][x] == bishop || board[y-i][x] == queen || (board[y-i][x] == king && i == 1))
				{
					*threat_x = x; *threat_y = y-i; 
					check = 1;
				}
				break;
			}
		}
	}
	
	return check;
}

/**********************************************************************************************
Function: check_king

Ojective: Given the kings color, verify if he is under threat.

Arguments:
	board[][] --> contains the entire board with each pieces position
	color --> color of king
	*threat_x, *threat_y --> first piece that is found to be attacking the king

Return value:
	returns 1 is the king is in fact under attack, 0 otherwise
	
**********************************************************************************************/
int check_king(char board[8][8], char color, int *threat_x, int *threat_y)
{
	int x=0, y=0;
	int aux, aux1, aux2;
	get_king_pos(board, color, &x, &y);

	aux = threats(board, x, y, color, &aux1, &aux2);

	if(aux != 0 && threat_x != NULL && threat_y != NULL)
	{
		*threat_x = aux1;
		*threat_y = aux2;
	}

	return aux;
}

/**********************************************************************************************
Function: verify_different_colors

Ojective: Given two pieces, verify if they are the same color. This is based on the
	casing of the character that represents the piece

Arguments:
	piece1, piece2 --> pieces to be compared

Return value:
	returns 1 if the pieces have different colors.
**********************************************************************************************/
int verify_different_colors(char piece1, char piece2)
{
	if((int)piece1 >= 97 && (int)piece1 <= 122 && (int)piece2 >= 97 && (int)piece2 <= 122)
		return 0;
	if((int)piece1 >= 65 && (int)piece1 <= 90 && (int)piece2 >= 65 && (int)piece2 <= 90)
		return 0;
	return 1;
}

/**********************************************************************************************
Function: adjacent_threats

Ojective: It checks if there is any square around without being threatened. This will be used
	to verify if the king can escape.

Arguments:
	board[][] --> contains the entire board with each pieces position
	color --> color of the threatning pieces

Return value:
	it returns 0 if there is at least one available position, returns 1 otherwise.
**********************************************************************************************/
int adjacent_threats(char board[8][8], int x, int y, char color)
{
	char piece;
	int check = 1;
	int aux1, aux2;

	piece = board[y][x];
	board[y][x] = '_';

	if(x+1 < 8)
	{
		if(verify_different_colors(piece, board[y][x+1]))
		{
			check = threats(board, x+1, y, color, &aux1, &aux2);
			if(check == 0)
			{
				board[y][x] = piece;
				return 0;
			}
		}
	}
	if(x+1 < 8 && y+1 < 8)
	{
		if(verify_different_colors(piece, board[y+1][x+1]))
		{
			check = threats(board, x+1, y+1, color, &aux1, &aux2);
			if(check == 0)
			{
				board[y][x] = piece;
				return 0;
			}
		}
	}
	if(y+1 < 8)
	{
		if(verify_different_colors(piece, board[y+1][x]))
		{
			check = threats(board, x, y+1, color, &aux1, &aux2);
			if(check == 0)
			{
				board[y][x] = piece;
				return 0;
			}
		}
	}
	if(x-1 >= 0 && y+1 < 8)
	{
		if(verify_different_colors(piece, board[y+1][x-1]))
		{
			check = threats(board, x-1, y+1, color, &aux1, &aux2);
			if(check == 0)
			{
				board[y][x] = piece;
				return 0;
			}
		}
	}
	if(x-1 >= 0)
	{
		if(verify_different_colors(piece, board[y][x-1]))
		{
			check = threats(board, x-1, y, color, &aux1, &aux2);
			if(check == 0)
			{
				board[y][x] = piece;
				return 0;
			}
		}
	}
	if(x-1 >= 0 && y-1 >= 0)
	{
		if(verify_different_colors(piece, board[y-1][x-1]))
		{
			check = threats(board, x-1, y-1, color, &aux1, &aux2);
			if(check == 0)
			{
				board[y][x] = piece;
				return 0;
			}
		}
	}
	if(y-1 >= 0)
	{
		if(verify_different_colors(piece, board[y-1][x]))
		{
			check = threats(board, x, y-1, color, &aux1, &aux2);
			if(check == 0)
			{
				board[y][x] = piece;
				return 0;
			}
		}
	}
	if(x+1 < 8 && y-1 >= 0)
	{
		if(verify_different_colors(piece, board[y-1][x+1]))
		{
			check = threats(board, x+1, y-1, color, &aux1, &aux2);
			if(check == 0)
			{
				board[y][x] = piece;
				return 0;
			}
		}
	}
	board[y][x] = piece;
	return 1;
}

/**********************************************************************************************
Function: move_reverse

Ojective: This function is used for saving and reversing plays. When reverse=0, this
	function will save the play inserted. If reverse=1, it will undo the last saved play.

Arguments:
	board[][] --> contains the entire board with each pieces position
	x_i, y_i --> initial coodinates of the piece
	x_f, y_f --> final coodinates of the piece

Return value:
	it doesn't return anything
**********************************************************************************************/
void move_reverse(char board[8][8], int x_i, int y_i, int x_f, int y_f, int reverse)
{
	static int xi=0, xf=0, yi=0, yf=0;
	static char piece;
	if(reverse == 0)
	{
		xi = x_i; xf = x_f; yi = y_i; yf = y_f;
		piece = board[yf][xf];
		board[yf][xf] = board[yi][xi];
		board[yi][xi] = '_';
	}
	else
	{
		board[yi][xi] = board[yf][xf];
		board[yf][xf] = piece;
	}
}

/**********************************************************************************************
Function: move_to_pos

Ojective: Checks if any piece of a given color can move to a certain positions. This will be
	used to verify if a king is under checkmate or not.

Arguments:
	board[][] --> contains the entire board with each pieces position
	x, y --> coordinates of the positions that a piece should move to
	*en_passant --> column that has a pawn that moved 2 squares in the last move, -1 otherwise
	color --> color of the pieces that should move to that square
	

Return value:
	returns 1 if there is indeed a piece that can move to a certain position without leaving
	the king in check
**********************************************************************************************/
int move_to_pos(char board[8][8], int x, int y, int *en_passant, char color, int castling[2][2])
{
	//king not considered, it shouldnt be necessary
	char pawn, bishop, knight, rook, queen;
	int i;
	char piece;
	int aux;

	if(color == 'w')
	{
		pawn = 'p';
		bishop = 'b';
		knight = 'n';
		rook = 'r';
		queen = 'q';
	}
	else
	{
		pawn = 'P';
		bishop = 'B';
		knight = 'N';
		rook = 'R';
		queen = 'Q';
	}

	for (i = 0; y+i < 8; i++)
	{
		if(board[y+i][x] != '_')
		{
			if(board[y+i][x] == rook || board[y+i][x] == queen)
			{
				move_reverse(board, x, y+i, x, y, 0);
				if(check_king(board, color, NULL, NULL))
				{
					move_reverse(board, x, y+i, x, y, 1);
					return 1;
				}
				move_reverse(board, x, y+i, x, y, 1);
			}
			break;
		}
	}
	for (i = 0; y-i >= 0; i++)
	{
		if(board[y-i][x] != '_')
		{
			if(board[y-i][x] == rook || board[y-i][x] == queen)
			{
				move_reverse(board, x, y-i, x, y, 0);
				if(check_king(board, color, NULL, NULL))
				{
					move_reverse(board, x, y-i, x, y, 1);
					return 1;
				}
				move_reverse(board, x, y-i, x, y, 1);
			}
			break;
		}
	}
	for (i = 0; x+i < 8; i++)
	{
		if(board[y][x+i] != '_')
		{
			if(board[y][x+i] == rook || board[y][x+i] == queen)
			{
				move_reverse(board, x+i, y, x, y, 0);
				if(check_king(board, color, NULL, NULL))
				{
					move_reverse(board, x+i, y, x, y, 1);
					return 1;
				}
				move_reverse(board, x+i, y, x, y, 1);
			}
			break;
		}
	}
	for (i = 0; x-i >= 0; i++)
	{
		if(board[y][x-i] != '_')
		{
			if(board[y][x-i] == rook || board[y][x-i] == queen)
			{
				move_reverse(board, x-i, y, x, y, 0);
				if(check_king(board, color, NULL, NULL) == 0)
				{
					move_reverse(board, x-i, y, x, y, 1);
					return 1;
				}
				move_reverse(board, x-i, y, x, y, 1);
			}
			break;
		}
	}

	for(i = 0; x+i < 8 && y+i < 8; i++)
	{
		if(board[y+i][x+i] != '_')
		{
			if(board[y+i][x+i] == bishop || board[y+i][x+i] == queen)
			{
				move_reverse(board, x+i, y+i, x, y, 0);
				if(check_king(board, color, NULL, NULL) == 0)
				{
					move_reverse(board, x+i, y+i, x, y, 1);
					return 1;
				}
				move_reverse(board, x+i, y+i, x, y, 1);
			}
			break;
		}
	}
	for(i = 0; x+i < 8 && y-i >= 0; i++)
	{
		if(board[y-i][x+i] != '_')
		{
			if(board[y-i][x+i] == bishop || board[y-i][x+i] == queen)
			{
				move_reverse(board, x+i, y-i, x, y, 0);
				if(check_king(board, color, NULL, NULL) == 0)
				{
					move_reverse(board, x+i, y-i, x, y, 1);
					return 1;
				}
				move_reverse(board, x+i, y-i, x, y, 1);
			}
			break;
		}
	}
	for(i = 0; x-i >= 0 && y+i < 8; i++)
	{
		if(board[y+i][x-i] != '_')
		{
			if(board[y+i][x-i] == bishop || board[y+i][x-i] == queen)
			{
				move_reverse(board, x-i, y+i, x, y, 0);
				if(check_king(board, color, NULL, NULL) == 0)
				{
					move_reverse(board, x-i, y+i, x, y, 1);
					return 1;
				}
				move_reverse(board, x-i, y+i, x, y, 1);
			}
			break;
		}
	}
	for(i = 0; x-i >= 0 && y-i >= 0; i++)
	{
		if(board[y-i][x-i] != '_')
		{
			if(board[y-i][x-i] == bishop || board[y-i][x-i] == queen)
			{
				move_reverse(board, x-i, y-i, x, y, 0);
				if(check_king(board, color, NULL, NULL) == 0)
				{
					move_reverse(board, x-i, y-i, x, y, 1);
					return 1;
				}
				move_reverse(board, x-i, y-i, x, y, 1);
			}
			break;
		}
	}

	if(x+1 < 8 && y+2 < 8 && board[y+2][x+1] == knight)
	{
		move_reverse(board, x+1, y+2, x, y, 0);
		if(check_king(board, color, NULL, NULL) == 0)
		{
			move_reverse(board, x+1, y+2, x, y, 1);
			return 1;
		}
		move_reverse(board, x+1, y+2, x, y, 1);
	}
	if(x+1 < 8 && y-2 >= 0 && board[y-2][x+1] == knight)
	{
		move_reverse(board, x+1, y-2, x, y, 0);
		if(check_king(board, color, NULL, NULL) == 0)
		{
			move_reverse(board, x+1, y-2, x, y, 1);
			return 1;
		}
		move_reverse(board, x+1, y-2, x, y, 1);
	}
	if(x-1 >= 0 && y+2 < 8 && board[y+2][x-1] == knight)
	{
		move_reverse(board, x-1, y+2, x, y, 0);
		if(check_king(board, color, NULL, NULL) == 0)
		{
			move_reverse(board, x-1, y+2, x, y, 1);
			return 1;
		}
		move_reverse(board, x-1, y+2, x, y, 1);
	}
	if(x-1 >= 0 && y-2 >= 0 && board[y-2][x-1] == knight)
	{
		move_reverse(board, x-1, y-2, x, y, 0);
		if(check_king(board, color, NULL, NULL) == 0)
		{
			move_reverse(board, x-1, y-2, x, y, 1);
			return 1;
		}
		move_reverse(board, x-1, y-2, x, y, 1);
	}
	if(x+2 < 8 && y+1 < 8 && board[y+1][x+2] == knight)
	{
		move_reverse(board, x+2, y+1, x, y, 0);
		if(check_king(board, color, NULL, NULL) == 0)
		{
			move_reverse(board, x+2, y+1, x, y, 1);
			return 1;
		}
		move_reverse(board, x+2, y+1, x, y, 1);
	}
	if(x+2 < 8 && y-1 >= 0 && board[y-1][x+2] == knight)
	{
		move_reverse(board, x+2, y-1, x, y, 0);
		if(check_king(board, color, NULL, NULL) == 0)
		{
			move_reverse(board, x+2, y-1, x, y, 1);
			return 1;
		}
		move_reverse(board, x+2, y-1, x, y, 1);
	}
	if(x-2 >= 0 && y+1 < 8 && board[y+1][x-2] == knight)
	{
		move_reverse(board, x-2, y+1, x, y, 0);
		if(check_king(board, color, NULL, NULL) == 0)
		{
			move_reverse(board, x-2, y+1, x, y, 1);
			return 1;
		}
		move_reverse(board, x-2, y+1, x, y, 1);
	}
	if(x-2 >= 0 && y-1 >= 0 && board[y+2][x+1] == knight)
	{
		move_reverse(board, x-2, y-1, x, y, 0);
		if(check_king(board, color, NULL, NULL) == 0)
		{
			move_reverse(board, x-2, y-1, x, y, 1);
			return 1;
		}
		move_reverse(board, x-2, y-1, x, y, 1);
	}

	if(x+1 < 8 && y+1 < 8 && board[y+1][x+1] == pawn)
	{
		piece = board[y+1][x+1];
		aux = *en_passant;
		if(piece_move(board, color, x+1, y+1, x, y, &aux, castling))
		{
			if(check_king(board, color, NULL, NULL) == 0)
			{
				board[y][x] = board[y+1][x+1];
				board[y+1][x+1] = piece;
				return 1;
			}
			board[y][x] = board[y+1][x+1];
			board[y+1][x+1] = piece;
		}
	}
	if(x+1 < 8 && board[y][x+1] == pawn)
	{
		piece = board[y][x+1];
		aux = *en_passant;
		if(piece_move(board, color, x+1, y, x, y, &aux, castling))
		{
			if(check_king(board, color, NULL, NULL) == 0)
			{
				board[y][x] = board[y][x+1];
				board[y][x+1] = piece;
				return 1;
			}
			board[y][x] = board[y][x+1];
			board[y][x+1] = piece;
		}
	}
	if(x+1 < 8 && y-1 >= 0 && board[y-1][x+1] == pawn)
	{
		piece = board[y-1][x+1];
		aux = *en_passant;
		if(piece_move(board, color, x+1, y-1, x, y, &aux, castling))
		{
			if(check_king(board, color, NULL, NULL) == 0)
			{
				board[y][x] = board[y-1][x+1];
				board[y-1][x+1] = piece;
				return 1;
			}
			board[y][x] = board[y-1][x+1];
			board[y-1][x+1] = piece;
		}
	}
	if(y+1 < 8 && board[y+1][x] == pawn)
	{
		piece = board[y+1][x];
		aux = *en_passant;
		if(piece_move(board, color, x, y+1, x, y, &aux, castling))
		{
			if(check_king(board, color, NULL, NULL) == 0)
			{
				board[y][x] = board[y+1][x];
				board[y+1][x] = piece;
				return 1;
			}
			board[y][x] = board[y+1][x];
			board[y+1][x] = piece;
		}
	}
	if(y-1 >= 0 && board[y-1][x] == pawn)
	{
		piece = board[y-1][x];
		aux = *en_passant;
		if(piece_move(board, color, x, y-1, x, y, &aux, castling))
		{
			if(check_king(board, color, NULL, NULL) == 0)
			{
				board[y][x] = board[y-1][x];
				board[y-1][x] = piece;
				return 1;
			}
			board[y][x] = board[y-1][x];
			board[y-1][x] = piece;
		}
	}
	if(x-1 >= 0 && y+1 < 8 && board[y+1][x-1] == pawn)
	{
		piece = board[y+1][x-1];
		aux = *en_passant;
		if(piece_move(board, color, x-1, y+1, x, y, &aux, castling))
		{
			if(check_king(board, color, NULL, NULL) == 0)
			{
				board[y][x] = board[y+1][x-1];
				board[y+1][x-1] = piece;
				return 1;
			}
			board[y][x] = board[y+1][x-1];
			board[y+1][x-1] = piece;
		}
	}
	if(x-1 >= 0 && board[y][x-1] == pawn)
	{
		piece = board[y][x-1];
		aux = *en_passant;
		if(piece_move(board, color, x-1, y, x, y, &aux, castling))
		{
			if(check_king(board, color, NULL, NULL) == 0)
			{
				board[y][x] = board[y][x-1];
				board[y][x-1] = piece;
				return 1;
			}
			board[y][x] = board[y][x-1];
			board[y][x-1] = piece;
		}
	}
	if(x-1 >= 0 && y-1 >= 0 && board[y-1][x-1] == pawn)
	{
		piece = board[y-1][x-1];
		aux = *en_passant;
		if(piece_move(board, color, x-1, y-1, x, y, &aux, castling))
		{
			if(check_king(board, color, NULL, NULL) == 0)
			{
				board[y][x] = board[y-1][x-1];
				board[y-1][x-1] = piece;
				return 1;
			}
			board[y][x] = board[y-1][x-1];
			board[y-1][x-1] = piece;
		}
	}
	return 0;
}

/**********************************************************************************************
Function: get_color

Ojective: It identifies the color of a specific piece.

Arguments:
	piece --> piece from which the color is to be determined
	

Return value:
	returns 'w' for white and 'b' for black
**********************************************************************************************/
char get_color(char piece)
{
	if(piece >= 97 && piece <= 122)
		return 'w';
	if(piece >= 65 && piece <= 90)
		return 'b';
	return '\0';
}

/**********************************************************************************************
Function: get_opposite_color

Ojective: It identifies the color of a specific piece and returns the opposite.

Arguments:
	piece --> piece from which the color is to be determined
	

Return value:
	returns 'w' for black and 'b' for white
**********************************************************************************************/
char get_opposite_color(char piece)
{
	if(piece >= 97 && piece <= 122)
		return 'b';
	if(piece >= 65 && piece <= 90)
		return 'w';
	return '\0';
}

/**********************************************************************************************
Function: eat_block_threats

Ojective: This function will be used to determine if king can escape a threat by eating it or
	blocking it with another piece.

Arguments:
	board[][] --> contains the entire board with each pieces position
	king_x, king_y --> position of the king
	threat_x, threat_y --> position of the threat
	*en_passant --> column that has a pawn that moved 2 squares in the last move, -1 otherwise

Return value:
	returns 1 if the threatning piece can be blocked or eaten. returns 0 otherwise.
**********************************************************************************************/
int eat_block_threat(char board[8][8], int king_x, int king_y, int threat_x, int threat_y, int *en_passant, int castling[2][2])
{
	int increment_x=0, increment_y=0;
	char color;
	int i;

	color = get_color(board[king_y][king_x]);

	if(board[threat_y][threat_x] == 'n' || board[threat_y][threat_x] == 'N')
	{
		return move_to_pos(board, threat_x, threat_y, en_passant, color, castling);
	}

	if(threat_x - king_x != 0)
		increment_x = (threat_x - king_x)/abs(threat_x - king_x);

	if(threat_y - king_y != 0)
		increment_y = (threat_y - king_y)/abs(threat_y - king_y);

	for (i = 0; threat_x+increment_x*i != king_x || threat_y+increment_y*i != king_y; i++)
	{
		if(move_to_pos(board, threat_x+increment_x*i, threat_y+increment_y*i, en_passant, color, castling))
		{
			return 1;
		}
	}
	return 0;
}

/**********************************************************************************************
Function: draw

Ojective: Verifies if there is enough material to do a checkmate.

Arguments:
	board[][] --> contains the entire board with each pieces position

Return value:
	returns 1 if there isn't enough material to do checkmate from both sides, 0 otherwise
**********************************************************************************************/
int draw(char board[8][8])
{
	int i=0, j=0;
	int white=0, black=0;
	for (i = 0; i < B_SIZE; i++)
	{
		for (j = 0; j < B_SIZE; j++)
		{
			if(board[i][j] == 'p' || board[i][j] == 'P' ||
				board[i][j] == 'q' || board[i][j] == 'Q' ||
				board[i][j] == 'r' || board[i][j] == 'R')
				return 0;
			if(board[i][j] == 'b' || board[i][j] == 'n')
				white++;
			if(board[i][j] == 'B' || board[i][j] == 'N')
				black++;

			if(white > 1 || black > 1)
				return 0;
		}
	}
	return 1;
}

/**********************************************************************************************
Function: stale_mate

Ojective: verifies if the player can make any move, if it is a stale mate or not

Arguments:
	board[][] --> contains the entire board with each pieces position
	*en_passant --> column that has a pawn that moved 2 squares in the last move, -1 otherwise
	color --> color of the player that is possibly unable to make any valid move

Return value:
	returns 1 if there isn't enough material to do checkmate from both sides, 0 otherwise
**********************************************************************************************/
int stale_mate(char board[8][8], char color, int *en_passant, int castling[2][2])
{

	int aux;
	char pawn, bishop, knight, rook, queen;
	char piece;
	int i=0, j=0;
	int stale = 1;

	if(color == 'w')
	{
		pawn = 'p';
		bishop = 'b';
		knight = 'n';
		rook = 'r';
		queen = 'q';
	}
	else
	{
		pawn = 'P';
		bishop = 'B';
		knight = 'N';
		rook = 'R';
		queen = 'Q';
	}

	for (i = 0; i < B_SIZE; i++)
	{
		for (j = 0; j < B_SIZE; j++)
		{
			if(board[i][j] == pawn || board[i][j] == bishop ||
				board[i][j] == knight ||board[i][j] == rook ||
				board[i][j] == queen)
			{
				if(i+1 < 8 && j+1 < 8) 
				{
					aux = *en_passant;
					piece = board[i+1][j+1];
					if(piece_move(board, color, j, i, j+1, i+1, en_passant, castling))
					{
						board[i][j] = board[i+1][j+1];
						board[i+1][j+1] = piece;
						*en_passant = aux;
						stale = 0;
					}
				}
				if(i+1 < 8) 
				{
					aux = *en_passant;
					piece = board[i+1][j];
					if(piece_move(board, color, j, i, j, i+1, en_passant, castling))
					{
						board[i][j] = board[i+1][j];
						board[i+1][j] = piece;
						*en_passant = aux;
						stale = 0;
					}
				}
				if(i+1 < 8 && j-1 >= 0) 
				{
					aux = *en_passant;
					piece = board[i+1][j-1];
					if(piece_move(board, color, j, i, j-1, i+1, en_passant, castling))
					{
						board[i][j] = board[i+1][j-1];
						board[i+1][j-1] = piece;
						*en_passant = aux;
						stale = 0;
					}
				}
				if(j+1 < 8) 
				{
					aux = *en_passant;
					piece = board[i][j+1];
					if(piece_move(board, color, j, i, j+1, i, en_passant, castling))
					{
						board[i][j] = board[i][j+1];
						board[i][j+1] = piece;
						*en_passant = aux;
						stale = 0;
					}
				}
				if(j-1 >= 0) 
				{
					aux = *en_passant;
					piece = board[i][j-1];
					if(piece_move(board, color, j, i, j-1, i, en_passant, castling))
					{
						board[i][j] = board[i][j-1];
						board[i][j-1] = piece;
						*en_passant = aux;
						stale = 0;
					}
				}
				if(i-1 >= 0 && j+1 < 8) 
				{
					aux = *en_passant;
					piece = board[i-1][j+1];
					if(piece_move(board, color, j, i, j+1, i-1, en_passant, castling))
					{
						board[i][j] = board[i-1][j+1];
						board[i-1][j+1] = piece;
						*en_passant = aux;
						stale = 0;
					}
				}
				if(i-1 >= 0) 
				{
					aux = *en_passant;
					piece = board[i-1][j];
					if(piece_move(board, color, j, i, j, i-1, en_passant, castling))
					{
						board[i][j] = board[i-1][j];
						board[i-1][j] = piece;
						*en_passant = aux;
						stale = 0;
					}
				}
				if(i-1 >= 0 && j-1 >= 0) 
				{
					aux = *en_passant;
					piece = board[i-1][j-1];
					if(piece_move(board, color, j, i, j-1, i-1, en_passant, castling))
					{
						board[i][j] = board[i-1][j-1];
						board[i-1][j-1] = piece;
						*en_passant = aux;
						stale = 0;
					}
				}
			}
			if(stale == 0)
				break;
		}
		if(stale == 0)
			break;
	}
	return stale;
}

/**********************************************************************************************
Function: free_pieces

Ojective: verifies if the game is a draw or stale mate

Arguments:
	board[][] --> contains the entire board with each pieces position
	*en_passant --> column that has a pawn that moved 2 squares in the last move, -1 otherwise
	color --> color of the player that is possibly unable to make any valid move

Return value:
	returns a positive if it is a draw or a stale mate.
**********************************************************************************************/
/*it is missing the three fold repetition and 50 move rule. will also add
a rule that prevent more than 150 plays
*/
int free_pieces(char board[8][8], char color, int *en_passant, int castling[2][2])
{
	int ret_val = 0;

	ret_val += draw(board);
	ret_val += stale_mate(board, color, en_passant, castling);

	return ret_val;
}

/*
0 --> nothing
1 --> check
2 --> check mate
3 --> stale mate
*/
int check(char board[8][8], char color, int *en_passant, int castling[2][2])
{
	int x, y;
	int threat_x = -1, threat_y = -1;

	get_king_pos(board, color, &x, &y);

	if(check_king(board, color, &threat_x, &threat_y))
	{
		if(adjacent_threats(board, x, y, color) == 1)
		{
			return 1;
		}
		else
		{
			if(eat_block_threat(board, x, y, threat_x, threat_y, en_passant, castling))
			{
				return 1;
			}
			else
				return 2;
		}
	}
	else
	{
		if(adjacent_threats(board, x, y, color) == 1)
		{
			if(free_pieces(board, color, en_passant, castling) != 0)
				return 3;
		}
	}
	return 0;
}

//en_passant is not updated every time function returns 0
int piece_move(char board[8][8], char color, int x_i, int y_i, int x_f, int y_f, int *en_passant, int castling[2][2])
{
	int i;
	int increment_x, increment_y;
	char piece;
	int aux = *en_passant;
	int threat_x, threat_y;

	if(x_i == x_f && y_i == y_f)
		return 0;

	*en_passant = -1;

	if(board[y_i][x_i] > 'a' && board[y_i][x_i] < 'z' && color == 'b')
	{
		*en_passant = aux;
		return 0;
	}
	if(board[y_i][x_i] > 'A' && board[y_i][x_i] < 'Z' && color == 'w')
	{
		*en_passant = aux;
		return 0;
	}

	//pawn movement
	if(board[y_i][x_i] == 'p')
	{
		if(abs(y_f - y_i) > 2 || abs(x_f - x_i) >= 2 || y_f - y_i >= 0)
			return 0;
		if(y_f - y_i == -2 && x_f - x_i == 0)
		{
			if(y_i == 6)
			{
				if(board[y_i-1][x_i] == '_' && board[y_i-2][x_i] == '_')
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 0);
					if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
					{
						move_reverse(board, x_i, y_i, x_f, y_f, 1);
						*en_passant = aux;
						return 0;
					}
					else
					{
						*en_passant = x_f;
						return 1;
					}
				}
				else
				{
					*en_passant = aux;
					return 0;
				}
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
				
		}
		if(y_f - y_i == -1 && x_f - x_i == 0)
		{
			if(board[y_i-1][x_i] == '_')
			{
				move_reverse(board, x_i, y_i, x_f, y_f, 0);
				if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 1);
					*en_passant = aux;
					return 0;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
		}
		if(y_f - y_i == -1 && abs(x_f - x_i) == 1)
		{
			if(board[y_f][x_f] != '_')
			{
				if(verify_different_colors(board[y_i][x_i], board[y_f][x_f]))
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 0);
					if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
					{
						move_reverse(board, x_i, y_i, x_f, y_f, 1);
						*en_passant = aux;
						return 0;
					}
					else
					{
						return 1;
					}
				}
				else
				{
					*en_passant = aux;
					return 0;
				}
			}
			else if(y_f == 2 && x_f == aux)
			{
				move_reverse(board, x_i, y_i, x_f, y_f, 0);
				piece = board[y_f+1][x_f];
				board[y_f+1][x_f] = '_';
				if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
				{
					board[y_f+1][x_f] = piece;
					move_reverse(board, x_i, y_i, x_f, y_f, 1);
					*en_passant = aux;
					return 0;
				}
				else
					return 1;
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
		}
	}
	if(board[y_i][x_i] == 'P')
	{
		if(abs(y_f - y_i) > 2 || abs(x_f - x_i) >= 2 || y_f - y_i <= 0)
		{
			*en_passant = aux;
			return 0;
		}
		if(y_f - y_i == 2 && x_f - x_i == 0)
		{
			if(y_i == 1)
			{
				if(board[y_i+1][x_i] == '_' && board[y_i+2][x_i] == '_')
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 0);
					if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
					{
						move_reverse(board, x_i, y_i, x_f, y_f, 1);
						*en_passant = aux;
						return 0;
					}
					else
					{
						*en_passant = x_f;
						return 1;
					}
				}
				else
				{
					*en_passant = aux;
					return 0;
				}
			}
			else 
			{
				*en_passant = aux;
				return 0;
			}
				
		}
		if(y_f - y_i == 1 && x_f - x_i == 0)
		{
			if(board[y_i+1][x_i] == '_')
			{
				move_reverse(board, x_i, y_i, x_f, y_f, 0);
				if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 1);
					*en_passant = aux;
					return 0;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
		}
		if(y_f - y_i == 1 && abs(x_f - x_i) == 1)
		{
			if(board[y_f][x_f] != '_')
			{
				if(verify_different_colors(board[y_i][x_i], board[y_f][x_f]))
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 0);
					if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
					{
						move_reverse(board, x_i, y_i, x_f, y_f, 1);
						*en_passant = aux;
						return 0;
					}
					else
					{
						return 1;
					}
				}
				else
				{
					*en_passant = aux;
					return 0;
				}
			}
			else if(y_f == 5 && x_f == aux)
			{
				move_reverse(board, x_i, y_i, x_f, y_f, 0);
				piece = board[y_f-1][x_f];
				board[y_f-1][x_f] = '_';
				if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
				{
					board[y_f-1][x_f] = piece;
					move_reverse(board, x_i, y_i, x_f, y_f, 1);
					*en_passant = aux;
					return 0;
				}
				else
					return 1;
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
		}
	}

	//king movement
	if(board[y_i][x_i] == 'k' || board[y_i][x_i] == 'K')
	{
		if(x_f - x_i == 2 && y_f - y_i == 0)
		{
			if((y_i == 0 && castling[0][1] == 0) || (y_i == 7 && castling[1][1] == 0))
			{
				*en_passant = aux;
				return 0;
			}

			if(threats(board, x_i, y_i, get_color(board[y_i][x_i]), &threat_x, &threat_y))
			{
				*en_passant = aux;
				return 0;
			}
			for (i = 1; i < 3; i++)
			{
				if(threats(board, x_i+i, y_i, get_color(board[y_i][x_i]), &threat_x, &threat_y) || board[y_i][x_i+i] != '_')
				{
					*en_passant = aux;
					return 0;
				}
			}
			move_reverse(board, x_i, y_i, x_f, y_f, 0);
			move_reverse(board, x_i+i, y_i, x_f-1, y_f, 0);
			if(y_i == 0)
			{
				castling[0][0] = 0;
				castling[0][1] = 0;
			}
			else
			{
				castling[1][0] = 0;
				castling[1][1] = 0;
			}
			return 1;
		}
		if(x_f - x_i == -2 && y_f - y_i == 0)
		{
			if((y_i == 0 && castling[0][0] == 0) || (y_i == 7 && castling[1][0] == 0))
			{
				*en_passant = aux;
				return 0;
			}

			if(threats(board, x_i, y_i, get_color(board[y_i][x_i]), &threat_x, &threat_y))
			{
				*en_passant = aux;
				return 0;
			}
			for (i = 1; i < 3; i++)
			{
				if(threats(board, x_i-i, y_i, get_color(board[y_i][x_i]), &threat_x, &threat_y) || board[y_i][x_i-i] != '_')
				{
					*en_passant = aux;
					return 0;
				}
			}
			if(threats(board, x_i-i, y_i, get_color(board[y_i][x_i]), &threat_x, &threat_y) || board[y_i][x_i-i] != '_')
			{
				*en_passant = aux;
				return 0;
			}

			i++;
			move_reverse(board, x_i, y_i, x_f, y_f, 0);
			move_reverse(board, x_i-i, y_i, x_f+1, y_f, 0);
			if(y_i == 0)
			{
				castling[0][0] = 0;
				castling[0][1] = 0;
			}
			else
			{
				castling[1][0] = 0;
				castling[1][1] = 0;
			}
			return 1;
		}

		if(abs(x_f - x_i) <= 1 && abs(y_f - y_i) <= 1)
		{
			if(verify_different_colors(board[y_i][x_i], board[y_f][x_f]))
			{
				move_reverse(board, x_i, y_i, x_f, y_f, 0);
				if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 1);
					*en_passant = aux;
					return 0;
				}
				else
				{
					if(board[y_f][x_f] == 'K')
					{
						castling[0][0] = 0;
						castling[0][1] = 0;
					}
					else
					{
						castling[1][0] = 0;
						castling[1][1] = 0;
					}
					return 1;
				}
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
		}
		else
		{
			*en_passant = aux;
			return 0;
		}
	}

	//knight movement
	if((abs(x_f - x_i) == 2 && abs(y_f - y_i) == 1) || (abs(x_f - x_i) == 1 && abs(y_f - y_i) == 2))
	{
		if(board[y_i][x_i] == 'n' || board[y_i][x_i] == 'N')
		{
			if(verify_different_colors(board[y_i][x_i], board[y_f][x_f]))
			{
				move_reverse(board, x_i, y_i, x_f, y_f, 0);
				if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 1);
					*en_passant = aux;
					return 0;
				}
				else
					return 1;
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
		}
		else
		{
			*en_passant = aux;
			return 0;
		}
	}

	//bishop and queen
	i = 1;
	if(abs(x_f - x_i) == abs(y_f - y_i))
	{
		if (board[y_i][x_i] == 'b' || board[y_i][x_i] == 'B' || board[y_i][x_i] == 'q' || board[y_i][x_i] == 'Q')
		{
			increment_x = (x_f - x_i)/abs(x_f - x_i);
			increment_y = (y_f - y_i)/abs(y_f - y_i);

			while(x_i + increment_x*i < x_f || y_i + increment_y*i < y_f)
			{
				if(board[y_i+increment_y*i][x_i+increment_x*i] != '_')
				{
					*en_passant = aux;
					return 0;
				}
				i++;
			}

			if(verify_different_colors(board[y_i][x_i], board[y_f][x_f]))
			{
				move_reverse(board, x_i, y_i, x_f, y_f, 0);
				if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 1);
					*en_passant = aux;
					return 0;
				}
				else
					return 1;
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
		}
		else
		{
			*en_passant = aux;
			return 0;
		}
	}

	//rook and queen
	i = 1;
	if((abs(x_f - x_i) == 0 && abs(y_f - y_i) != 0) || (abs(x_f - x_i) != 0 && abs(y_f - y_i) == 0))
	{
		if (board[y_i][x_i] == 'r' || board[y_i][x_i] == 'R' || board[y_i][x_i] == 'q' || board[y_i][x_i] == 'Q')
		{
			if(x_f - x_i != 0)
			{
				increment_x = (x_f - x_i)/abs(x_f - x_i);
				increment_y = 0;
			}
			else
			{
				increment_x = 0;
				increment_y = (y_f - y_i)/abs(y_f - y_i);
			}			

			while(x_i + increment_x*i < x_f || y_i + increment_y*i < y_f)
			{
				if(board[y_i+increment_y*i][x_i+increment_x*i] != '_')
				{
					*en_passant = aux;
					return 0;
				}
				i++;
			}

			if(verify_different_colors(board[y_i][x_i], board[y_f][x_f]))
			{
				move_reverse(board, x_i, y_i, x_f, y_f, 0);
				if(check_king(board, get_color(board[y_f][x_f]), NULL, NULL))
				{
					move_reverse(board, x_i, y_i, x_f, y_f, 1);
					*en_passant = aux;
					return 0;
				}
				else
				{
					if(board[0][0] != 'R')
					{
						castling[0][0] = 0;
					}
					else if(board[0][7] != 'R')
					{
						castling[0][1] = 0;
					}
					else if(board[7][0] != 'r')
					{
						castling[1][0] = 0;
					}
					else if(board[7][7] != 'r')
					{
						castling[1][1] = 0;
					}
					return 1;
				}
			}
			else
			{
				*en_passant = aux;
				return 0;
			}
		}
		else
		{
			*en_passant = aux;
			return 0;
		}
	}
	else
	{
		*en_passant = aux;
		return 0;
	}

	*en_passant = aux;
	return 0;
}

//start by checking if it is checkmate and then verify if
//the move is possible(valid move and does not leave the king
//in check)
int move(char board[8][8], int x_i, int y_i, int x_f, int y_f, char upgrade, int *en_passant, int castling[2][2])
{
	char color;
	int check_val;

	color = get_color(board[y_i][x_i]);
	check_val = check(board, color, en_passant, castling);
	if(check_val >= 2)
		return check_val;
	return piece_move(board, color, x_i, y_i, x_f, y_f, en_passant, castling);
}

