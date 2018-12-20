#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define size_x 30
#define size_y 10
#define my_y 8 
#define my_x 2
#define spdi 100 
#define blki 501 //장애물 바뀌는 초기값

int speed=spdi;
int score=0;
int blocktime=blki;
int backgrd[size_y][size_x];

void before_game();
void backbase();
void drawback();
void jump(int a);
void makeblock();
int kbhit();
int get_ch();
void blockmoving();
int gameover();
void CheckScore();
int after_game();

