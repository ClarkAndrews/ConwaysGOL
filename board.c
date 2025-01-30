#include "board.h"

// allocate size depending on screen size
////////////////////////////////////////////////////////
char **define_board_size(int height, int width) {

  
  char **board= (char **)malloc(height * sizeof(char *));

  for(int row = 0; row < height; row++) {

    board[row] = (char *)malloc((width) * sizeof(char));

    for (int col = 0; col < width; col++){
      board[row][col] = ' ';
    }
  }

  return board;
}

// print board
////////////////////////////////////////////////////////
void print_board(char **board, int height, int width) {

    clear();
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width;col++){
        
          printw("%c", board[row][col]);
        }
          
    }

    refresh();
}

// free memory allocated to a board
////////////////////////////////////////////////////////
void destroy_board(char **board, int height) {
    
    for(int row = 0; row < height; row++) {         
       free(board[row]);            
    }
    free(board);
}

// add a cell to the board
////////////////////////////////////////////////////////
void add_cell(char **board, int y, int x) {

  if (board[y][x] != '#') {
    move(y, x);
    board[y][x] = '#';
    refresh();
  }
}

// remove a cell if there is one
void remove_cell(char **board, int y, int x){

  if (board[y][x] == '#') {

    move(y, x);
    board[y][x] = ' ';
    refresh();
  }
}


// count neighbors for each cell
/////////////////////////////////////////////////////////////////
int count_neighbors(char **board, int y, int x, int width, int height) {
  int newRow, newCol, count = 0;
  int offset[8][2] = {{-2,-1}, {0,-1}, {2,-1}, {-2,0}, {2,0}, {-2,1}, {0,1}, {2,1}};  

  // loop through offset and check for neighbors
  for(int i = 0; i < 8; i++){
    newCol = x + offset[i][0];
    newRow = y + offset[i][1];

    // check if newRow & newCol are on the board
    if(newRow >= 0 && newRow < height && newCol >= 0 && newCol < width) {

      if(board[newRow][newCol] == '#') {
        count++;
      }
    }
  }
  return count;  
}

// resize screen
///////////////////////////////////////////////////
void handle_screen_resize(char **board, int *height, int *width) {

  int newHeight, newWidth;

  getmaxyx(stdscr, newHeight, newWidth);

  // check if screen was actually resized
  // theoretically not necessary, but since the function runs in the game loop
  if(newHeight != *height || newWidth != *width) {
    handle_board_resize(board, *height, *width, newHeight, newWidth);

    // change height and width values
    *height = newHeight;
    *width = newWidth;
  
        
  }
}

// resize board
////////////////////////////////////////////////////////////////////
char **handle_board_resize(char **board, int height, int width, int newHeight, int newWidth) {

  // define newBoard
  char **newBoard = define_board_size(newHeight, newWidth);

  // compare row/col size with BOTH heights/widths (so you can resize in both directions)
  for(int row = 0; row < newHeight && row < height; row++) {
    for(int col = 0; col < newWidth && col < width; col++) {
      newBoard[row][col] = board[row][col];
    }
  }

  destroy_board(board, height);
  
 return newBoard; 
}
