#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constants declaration
const int maxrowlen = 3;
const int maxinputlen = 5;
const int x_player = 88;
const int o_player = 77;

void clear(){

  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void print2darray(int (*arr)[3]){
  /*prints the board, which happens to also be a 2d array*/
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < maxrowlen; j++){
      char boxcontent = arr[i][j]+'0';
      if( arr[i][j] == 88){
        printf("[%c]", 'X');
      }
      else if( arr[i][j] == 77){
        printf("[%c]", 'O');
      }
      else{
        printf("[%d]", boxcontent-'0');
      }
    }
    printf("\n");
  }
}

void fillarray(int (*arr)[3]){
  /*function to fill the array with 
  values that are not equal to each other*/
  int inc = 1;
  for(int y= 0; y < maxrowlen; y++){
    for(int x = 0; x < maxrowlen; x++){
       arr[y][x] = inc++;
    }
  }
}
int *translate_coordinate(int (*arr)[3], int choice){\
  /*function to translate 1-9 coordiantes into 
  the corresponding 2d array coordinates*/
  switch (choice) {
      case 1:
          return &arr[0][0];
      case 2:
          return &arr[0][1];
      case 3:
          return &arr[0][2];
      case 4:
          return &arr[1][0];
      case 5:
          return &arr[1][1];
      case 6:
          return &arr[1][2];
      case 7:
          return &arr[2][0];
      case 8:
          return &arr[2][1];
      case 9:
          return &arr[2][2];
      default:
        printf("NULL RETURNED");
        return NULL;
    }
}
int markboard(int (*arr)[3], int choice, int *ptr_playermark){
  /*
  function to mark the board using the coordinates with the playermark 
  88 = X player
  77 = O player
  */
  int *boardcoordinates = translate_coordinate(arr, choice);
  //do not DEREFERENCE A NULL POINTER
  if(boardcoordinates != NULL){
    if(!(*boardcoordinates == x_player || *boardcoordinates == o_player) ){
      *boardcoordinates = *ptr_playermark;
      printf("Marked!\nSwapping...\n");
      if (*ptr_playermark == x_player){
        *ptr_playermark = o_player;
      }else{
        *ptr_playermark = x_player;
      }
      return 0;
    }else{
      printf("Square is already marked!\n");
      return -1;
    }
  }else{
    printf("Invalid coordiantes!\n");
    return -1;
  }
}
void checkwin(int (*arr)[3], int *win){
  /*function to check the win instead of hard coding it, we can use a
  for loop instead for learning purposes
  */
  int horizontal_buffer[3];
  int vertical_buffer[3];
  int count_box_buffer = 0;

  for(int x = 0; x < maxrowlen; x++){
    for(int y = 0; y < maxrowlen; y++){
      horizontal_buffer[count_box_buffer] = arr[x][y];
      vertical_buffer[count_box_buffer] = arr[y][x];
      count_box_buffer++;
    }//END Y LOOP
    if( count_box_buffer == maxrowlen){
      //a == b && b == c shoudl do the proper check as per goolge
      int forwardslash_check = arr[0][0] == arr[1][1] && arr[2][2] == arr[1][1];
      int backslash_check = arr[0][2] == arr[1][1] && arr[2][0] == arr[1][1];
      if(
        ((horizontal_buffer[0] == horizontal_buffer[1]) && (horizontal_buffer[1] == horizontal_buffer[2])) || 
        ((vertical_buffer[0] == vertical_buffer[1]) && (vertical_buffer[1] == vertical_buffer[2])) ||
        forwardslash_check || backslash_check
      ){
        *win = 1;
        printf("We have a winner!...\nPress any key to play agian!\n");
        print2darray(arr);
        getchar();
        return;
      }else{
        memset(horizontal_buffer, 0, sizeof(horizontal_buffer));
        memset(vertical_buffer, 0, sizeof(vertical_buffer));
        count_box_buffer = 0;
      }
    }
  }//end x loop
  return;
}

void clearboard(int (*arr)[3]){
  /*implement a stale game checker someday*/
  return;
}
int main(void){
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
    
    *ptr_choice = atoi(buff);
    printf("You entered: %d\n", *ptr_choice);
    }while (markboard(board, choice, ptr_playermark));
    clear();
    checkwin(board, &win);
  }//end outer loop
  memset(board, 0, sizeof(board));
  win = 0;
  main(); 
}
