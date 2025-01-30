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
  
int main() {

  char *locale = setlocale(LC_CTYPE, NULL);
  wchar_t full_block = L'\u2588';
  
  int key, x = 0, y = 0;
  int height, width;
  
  initscr();
  keypad(stdscr, TRUE);
  noecho();

  // initial board
  getmaxyx(stdscr,height ,width );
  char **board = define_board_size(height, width);
  print_board(board, height, width);
  
  
  while(1){
  
    key = getch();

    if(key == KEY_RESIZE) {
      handle_screen_resize(board, &height, &width);
      // dont know if i can implement in time
    // move left
    } else if(key == KEY_LEFT) {
      x = x - 2;
      if(x < 0) x=0;
    // move right
    } else if(key == KEY_RIGHT) {
      x = x + 2;
      if(x > width-1) x=width-1;
    // move up
    } else if(key == KEY_UP) {
      y--;
      if(y < 0) y=0;
    // move down
    }else if(key == KEY_DOWN) {
      y++;
      if(y > height - 1) y=height-1;
    //add cell
    }else if(key == 'e') {
      add_cell(board, y, x);
    // remove cell
    }else if(key == 'r') {
      remove_cell(board, y, x);    
    }else if(key == ' ') {
      move(0, 0);
      run_game_of_live(board, height, width);
      refresh();
    }  
    print_board(board, height, width);
    
    move(y, x);
    refresh();
    
    key = 0;  
  }

  endwin();
  return 0;
}



void run_game_of_live(char **board, int height, int width) {

  // make getch()  non-blocking
  nodelay(stdscr, TRUE);

  // flags for controlling gameloop
  bool running = true;
  bool changesMade = true;
  
  // board to save the next generation state
  char **newBoard = define_board_size(height, width);
  int key;
    
   while (running) {

      key = getch();

      if(key == ' ' || !changesMade) {
        running = false;
      
      changesMade = false;
      
      for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
          int neighborCount = count_neighbors(board, row, col, width, height);

          // cell stays alive
          if ((neighborCount == 2 || neighborCount == 3) && board[row][col] == '#') {
            newBoard[row][col] = '#';
            // changesMade not set true because the cell stays alive
          // cell revives
          } else if (neighborCount == 3 && board[row][col] == ' ') {
            newBoard[row][col] = '#';
            changesMade = true;
          // cell dies
          } else if ((neighborCount < 2 || neighborCount > 3) && board[row][col] == '#') {
            newBoard[row][col] = ' ';
            changesMade = true;
          // cell stays the same (no change)
          } else {
            newBoard[row][col] = board[row][col];
          }
        }
      }

      // Copy newBoard to board for next gen
      for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
          board[row][col] = newBoard[row][col];
        }  
      }
      // Print the board and refresh screen
      print_board(board, height, width);
      refresh();
      napms(200);
    }


    // make getch() blocking again, non-block causes unewanted behavior in main-loop
    nodelay(stdscr,FALSE);
    // Free memory after the game ends
    destroy_board(newBoard, height);
  }
}

// check if boards are equal
bool compare_boards(char **board, char**newBoard, int height, int width) {
   for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (board[row][col] != newBoard[row][col]) {
                return false;
            }
        }
    }
    return true;
}
// allocate size depending on screen size
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
void destroy_board(char **board, int height) {
    
    for(int row = 0; row < height; row++) {         
       free(board[row]);            
    }
    free(board);
}

// add a cell to the board
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
