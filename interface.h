#ifndef INTERFACE
#define INTERFACE

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

bool initialization();
SDL_Window* open_window(int sq_size);
SDL_Renderer* create_renderer(SDL_Window *window);
SDL_Texture * create_sprite(SDL_Renderer *renderer);
void manage_moves(SDL_Renderer *renderer, SDL_Texture *sprite, char board[8][8], int sq_size, int (*move_p)(char [8][8], char, int, int, int, int, int*, int [2][2]), int *en_passant, int castling[2][2], char color, bool *quit);
void destroy(SDL_Window *window, SDL_Renderer *renderer);

#endif