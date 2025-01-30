#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>


char **define_board_size(int height, int width);
void print_board(char **board, int height, int width);
void destroy_board(char **board, int height);
void add_cell(char **board, int y, int x);
void remove_cell(char **board, int y, int x); 
void run_game_of_live(char **board, int height, int width);
int count_neighbors(char **board, int y, int x, int width, int height);
bool compare_boards(char **board, char**newBoard, int height, int width);
void handle_resize(char **board, int *height, int *width);
char **handle_board_resize(char **board, int height, int width, int newHeight, int newWidth);
void handle_screen_resize(char **board, int *height, int *width);
  
