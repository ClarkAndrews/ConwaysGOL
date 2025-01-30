#include "board.h"

void run_game_of_live(char **board, int height, int width);


int main() {
  
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
      handle_screen_resize(&board, &height, &width);
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

  destroy_board(board, height);
  endwin();
  return 0;
}

// game loop
//////////////////////////////////////////////////////
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
      }
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
    // Free memory after the game ends
  
    nodelay(stdscr,FALSE);
}
