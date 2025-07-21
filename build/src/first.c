/**
 * @file frist.c
 * @author Island, Rhoades
 * @brief modularized TTT(tictactoe in C implementation)
 * @version 1.2
 * @date 2025-07-21
 * 
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "first.h"

const int first;
const int maxrowlen = 3;
const  int maxinputlen = 5;
const  int x_player = 88;
const int o_player = 77;
const int first = 1;
const int max_marked_coordinates = 9;


const char *ascii_winner = 
    "__        ___                       _\n"
    "\\ \\      / (_)_ __  _ __   ___ _ __| |\n"
    " \\ \\ /\\ / /| | '_ \\| '_ \\ / _ \\ '__| |\n"
    "  \\ V  V / | | | | | | | |  __/ |  |_|\n"
    "   \\_/\\_/  |_|_| |_|_| |_|\\___|_|  (_)\n";

const char *ascii_stale = 
    " ____  _        _      _\n"
    "/ ___|| |_ __ _| | ___| |\n"
    "\\___ \\| __/ _` | |/ _ \\ |\n"
    " ___) | || (_| | |  __/_|\n"
    "|____/ \\__\\__,_|_|\\___(_)\n";

int marked_coordinates = 0;
int verbose_debug = 0;
int win = 0;
int stale = 0;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear(){
  /* clear the terminal */
  debug("Clearing\n");
  printf("\033[2J\033[1;1H");
}

void reset(){
  /* reset the win and stale counter */
  win = 0;
  stale = 0;
  return;
}
void check_stale(int (*arr)[3], int marked_coordinates){
  /**
   * @brief checks if the game has no winner and 
   * all the board is filled
   * 
   */
  if(marked_coordinates == max_marked_coordinates){
    marked_coordinates = 0;
    stale = 1;
    printf("%s", ascii_stale);
    printf("Press any key to continue...\n");
    print2darray(arr);
    getchar();
    clear();
  }
  return;
}
void debug(char *debug_info){
  /* prints if debug_info == 1, like dollar store verbose */
  if(verbose_debug){
    printf("%s", debug_info);
  }
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
  debug("Translate coordinates.\n");
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
        debug("translate_coordinate NULL RETURNED\n");
        return NULL;
    }
}
int markboard(int (*arr)[3], int choice, int *ptr_playermark, int *marked_coordinates){
  /*
  function to mark the board using the coordinates with the playermark 
  88 = X player
  77 = O player
  */
  debug("Markboard ran\n");
  int *boardcoordinates = translate_coordinate(arr, choice);
  //do not DEREFERENCE A NULL POINTER
  if(boardcoordinates != NULL){
    if(!(*boardcoordinates == x_player || *boardcoordinates == o_player) ){
      *boardcoordinates = *ptr_playermark;
      //the ++ does not work here, 
      *marked_coordinates += 1;
      debug("Marked!\nSwapping...\n");
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
    clear();
    printf("Invalid coordiantes!\n");
    return -1;
  }
}
void jet2holiday(){
  printf("nOtHiNg BeAtS a JeT2HolIdAy aNd RigHt"
    "NoW yOu CaN sAvE 50Lbs PeRpurrSun"
  );
  return;
}
void checkwin(int (*arr)[3], int *win){
  /*function to check the win instead of hard coding it, we can use a
  for loop instead for learning purposes
  */
  int horizontal_buffer[3];
  int vertical_buffer[3];
  int count_box_buffer = 0;

  for(int idx = 0; idx < maxrowlen; idx++){
    for(int idy = 0; idy < maxrowlen; idy++){
      horizontal_buffer[count_box_buffer] = arr[idx][idy];
      vertical_buffer[count_box_buffer] = arr[idy][idx];
      count_box_buffer++;
    }//END idy LOOP
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
        marked_coordinates = 0;
        
        printf("%s", ascii_winner);
        printf("Press any key to play agian!\n");
        print2darray(arr);
        getchar();
        clear();
        return;
      }else{
        debug("Clearing horizontal buffer\n");
        debug("Clearing vertical buffer\n");
        memset(horizontal_buffer, 0, sizeof(horizontal_buffer));
        memset(vertical_buffer, 0, sizeof(vertical_buffer));
        count_box_buffer = 0;
      }
    }
  }//end idx loop

  return;
}

