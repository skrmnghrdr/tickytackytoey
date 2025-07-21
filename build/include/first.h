//first header experimental

#ifndef FIRST_H
#define FIRST_H


extern const int maxrowlen;
extern const  int maxinputlen;
extern const  int x_player;
extern const int o_player;
extern const char *ascii_winner;
extern const char *ascii_stale;
extern const int max_marked_coordinates;
extern int marked_coordinates;
extern int verbose_debug;
extern int win;
extern int stale;

//experimental
void debug(char *debug_info);
void clear();

//board operations
void print2darray(int (*arr)[3]);
void fillarray(int (*arr)[3]);
int markboard(int (*arr)[3], int choice, int *ptr_playermark, int *marked_coordinates);

int *translate_coordinate(int (*arr)[3], int choice);
void checkwin(int (*arr)[3], int *win);
void check_stale(int (*arr)[3], int marked_coordinates);
void reset();
void jet2holiday();

#endif