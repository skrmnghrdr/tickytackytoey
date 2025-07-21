
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "first.h"

int main()
{
BEGIN_GAME:

  int board[3][3];
  fillarray(board);
  int playermark = x_player; 
  int *ptr_playermark = &playermark;
  int choice;
  int *ptr_choice = &choice;

  while(!(win || stale))
  {
    do
    {
      print2darray(board);
      char buff[maxinputlen];
      int n = 3;
      printf("Enter a coordiante:(1-9)\n");
      fgets(buff, n, stdin);
      *ptr_choice = atoi(buff);
      printf("You entered: %d\n", *ptr_choice);
    }while(markboard(board, choice, ptr_playermark, &marked_coordinates));

    clear();
    checkwin(board, &win);
    check_stale(board, marked_coordinates);
  }//end while

  memset(board, 0, sizeof(board));
  reset();

goto BEGIN_GAME; 

  return 0;
}