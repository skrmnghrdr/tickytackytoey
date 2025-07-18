#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//yes a 2d array would be esy if we would not use poniters, but pointters get 
//or add some more difficulty to it 


/*
resources used for reasearch
https://codedamn.com/news/c/how-to-use-pointers-with-2d-arrays-in-c
*/

/*notes: we need to send the array size so it can iterate correctly or we get out of mem bounds
it would not know the len of the function if we do not tell the function to do so

void print2darray(int (*arr)[5], int rows);
*/
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
  /*to fill the array with values 1-9*/
  //edit checkwin function to stop winning if 0
  int inc = 1;
  for(int y= 0; y < maxrowlen; y++){
    for(int x = 0; x < maxrowlen; x++){
       arr[y][x] = inc++;
    }
  }
}
int *translate_coordinate(int (*arr)[3], int choice){\
  //why is it not getting here
  printf("Translate ran\n");
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
  printf("Translating coordinates\n");
  int *boardcoordinates = translate_coordinate(arr, choice);
  printf("98 line\n");

  //do not DEREFERENCE A NULL POINTER<
  //YOU LITERALLY MELTED DOWN 2 HOURS
  //MFR YOU FINALLY GOT IT. GO TO SLEEp[]
  if(boardcoordinates != NULL){
    printf("booard coordintes should not be ran");

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
      //clear();
      printf("Square is already marked!\n");
      return -1;
    }
  }else{
    //clear();
    printf("Invalid coordiantes!\n");
    
    return -1;
  }
}
void checkwin(int (*arr)[3], int *win){
  /*putting the check in the y only does one row,
  puttin in the x only does 2 rows, traced theflow and realized it should be done after the Y*/
  int horizontal_buffer[3];
  int vertical_buffer[3];
  int count_box_buffer = 0;

  for(int x = 0; x < maxrowlen; x++){
    printf("x loop ran\n");
      //we should check it here then, before Y even starts so we could control the flow before we start appending shit 
    for(int y = 0; y < maxrowlen; y++){
      printf("Y looop ran\n");
        //fix loop here, make sure it hits the countboxbuff;
          //something wrong with the loop on how it appends the second row
      horizontal_buffer[count_box_buffer] = arr[x][y];
      vertical_buffer[count_box_buffer] = arr[y][x];
      count_box_buffer++;
          //something is wrong here, does not proceed to the next row or column what so eveer
    }//END Y LOOP
    if( count_box_buffer == maxrowlen){
          //x == y == z is a horrible way to see if 
          //three things are equal
          //a == b && b == c shoudl do the trick as per goolge
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
        //printf("memset run...\n");
        //printf("Vertical buffer %d %d %d:\n", vertical_buffer[0], vertical_buffer[1], vertical_buffer[2]);
        //printf("Horizontal buffer %d %d %d:\n", horizontal_buffer[0], horizontal_buffer[1], horizontal_buffer[2]);
        memset(horizontal_buffer, 0, sizeof(horizontal_buffer));
        memset(vertical_buffer, 0, sizeof(vertical_buffer));
        count_box_buffer = 0;
      }
      //manually check diagonals

      
    }
  }//end x loop
  return;
}

void clearboard(int (*arr)[3]){

  return;
}
int main(void){
    //the array is already a pointer, so it would throw if we put &board, 
    //we are sending the max elements of the father array to the function, and the rows are the rows inside,
    //todo:
    /*

    */
  int board[3][3];
  fillarray(board);
  //rep;ace with user input someday heere
  int playermark = x_player; 
  int *ptr_playermark = &playermark;
  int choice;
  int *ptr_choice = &choice;
  int win = 0;

  while(!win)
  {
  do{
    //to get the input from the user
    print2darray(board);
    char buff[maxinputlen];
    int n = 3;
    printf("Enter a coordiante:(1-9)\n");
    
    fgets(buff, n, stdin);
    
    //somehow there is a segmentation fault here
    //fixed the seg fault, do not dereference a null pointer please
    *ptr_choice = atoi(buff);
    printf("You entered: %d\n", *ptr_choice);

    
    }while (markboard(board, choice, ptr_playermark));
    clear();
    checkwin(board, &win);
  }//end outer loop
  
  //AS THE stack overflow said, the size is a long int,
  //don't print it as an int 
  //printf("Size:%zu bytes\n", sizeof(board[0]));
  memset(board, 0, sizeof(board));
  //fix the last issue here 
  /*
  might probably include a break here since it has to loop for ages till it starts a new game again lmaoo
  also put a stale detector here, we should mange each content of the array nd when it is full, we then reset it or call stale if there is no winner here
  */
  win = 0;


  main(); //lmao start again 

}
