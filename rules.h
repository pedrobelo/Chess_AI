#ifndef RULES
#define RULES

int check(char board[8][8], char color, int *en_passant, int castling[2][2]);
int piece_move(char board[8][8], char color, int x_i, int y_i, int x_f, int y_f, int *en_passant, int castling[2][2]);
int move(char board[8][8], int x_i, int y_i, int x_f, int y_f, char upgrade, int *en_passant, int castling[2][2]);

#endif