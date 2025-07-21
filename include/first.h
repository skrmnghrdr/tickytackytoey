//first header experimental

#ifndef FIRST_H
#define FIRST_H

extern const int first;
extern const int maxrowlen;
extern const  int maxinputlen;
extern const  int x_player;
extern const int o_player;
extern const char *ascii_winner;
extern const char *ascii_stale;
extern const int max_marked_coordinates;
extern int marked_coordinates;
extern int debug_info;

//experimental/developing  functions
void debug(char *debug_info);
int get_input(char *buff, int len);

void print_first();
int testfunct();
void clear();
//board operations
void print2darray(int (*arr)[3]);
void fillarray(int (*arr)[3]);
int markboard(int (*arr)[3], int choice, int *ptr_playermark, int *marked_coordinates);

int *translate_coordinate(int (*arr)[3], int choice);
void checkwin(int (*arr)[3], int *win);
int check_stale(int marked_coordinates);

#endif