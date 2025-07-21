
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "first.h"

int main(){

BEGIN_GAME:
  int board[3][3];
  fillarray(board);
  int playermark = x_player; 
  int *ptr_playermark = &playermark;
  int choice;
  int *ptr_choice = &choice;
  int win = 0;

  while(!win)
  {
  do{
    print2darray(board);
    char buff[maxinputlen];
    int n = 3;
    printf("Enter a coordiante:(1-9)\n");
    fgets(buff, n, stdin);
    //get_input(buff, maxinputlen);
    
    *ptr_choice = atoi(buff);
    printf("You entered: %d\n", *ptr_choice);
    }while (markboard(board, choice, ptr_playermark, &marked_coordinates));
    clear();
    checkwin(board, &win);
    if(check_stale(marked_coordinates)){
      printf("%s", ascii_stale);
      //is it recommended to change the variabel directly
      marked_coordinates = 0;
      break;
    }//put a clear board on the win you would need
    
  }//end outer loop
  memset(board, 0, sizeof(board));
  win = 0;
goto BEGIN_GAME; 
  return 0;
}