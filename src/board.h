#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>





char **define_board_size(int height, int width);
void print_board(char **board, int height, int width);
void destroy_board(char **board, int height);
void add_cell(char **board, int y, int x);
void remove_cell(char **board, int y, int x); 
int count_neighbors(char **board, int y, int x, int width, int height);
bool compare_boards(char **board, char**newBoard, int height, int width);
void handle_resize(char ***board, int *height, int *width);
  
