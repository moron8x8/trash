// gcc -std=gnu11 -Wall -Wextra -Wpedantic \
//     -fsanitize=address,undefined gamearc.c -o gamearc \
//     -lncurses -lm

#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define width 65
#define height 25

typedef struct {
    float x, y;
    int ix, iy;
    float dx, dy;
}Tball;

typedef struct{
    int x, y;
    int w;
} TRacket;
TRacket racket;
Tball ball;
int hitCount = 0;
int maxhitCount = 0;

char world[height][width];



void putBall(){
    if (ball.iy >= 0 && ball.iy < height && ball.ix >= 0 && ball.ix < width) {
        world[ball.iy][ball.ix] = '*';
    }
}

void moveBall(float x, float y){
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);

}
void initBall(){
    if(rand() % 2 == 0){
        ball.dx = 0.4;
    }else ball.dx = -0.4;

    ball.dy = -0.3 - ((rand() % 20) / 100.0);
}

void autoMoveBall(){
    float nextX = ball.x + ball.dx;
    float nextY = ball.y + ball.dy;
    int next_ix = (int)round(nextX);
    int next_iy = (int)round(nextY);

    if (next_ix >= 0 && next_ix < width && ball.iy >= 0 && ball.iy < height) {
        if (world[ball.iy][next_ix] == '#') {
            ball.dx = -ball.dx;
        }
    }

    if (ball.ix >= 0 && ball.ix < width && next_iy >= 0 && next_iy < height) {
        if (world[next_iy][ball.ix] == '#' || world[next_iy][ball.ix] == '=') { 
            ball.dy = -ball.dy;
        }
        else if (world[next_iy][ball.ix] == '@') {
            ball.dy = -ball.dy;
            float hitPosition = (ball.x - racket.x) / racket.w;
            ball.dx = 0.8 * (hitPosition - 0.5);
            hitCount++;
        }
    }


    moveBall(ball.x + ball.dx, ball.y + ball.dy);

}
void initRocket(){
    racket.w = 7;
    racket.x = (width - racket.w) / 2;
    racket.y = height - 1;
}

void putRacket(){
    for (int i = racket.x; i < racket.x + racket.w; i++) world[racket.y][i] = '@';
}


void initWorld(){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            if (i == 0 || i == width - 1 || j == 0) world[j][i] = '#';
            else if (j == 20 && i >= 20 && i <= 45) {
                world[j][i] = '='; 
            }
            else world[j][i] = ' ';
        }
    }
}

void show(){
    clear();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printw("%c", world[i][j]);
        }
        printw("\n");
    }
    mvprintw(height + 1, 2, "Count: %d", hitCount);
    mvprintw(height + 1, 20, "Max count: %d", maxhitCount);
    refresh();
}

void movePacket(int x){
    for(int i = 1; i < width - 1; i++) world[racket.y][i] = ' ';

    racket.x = x;
    if(racket.x < 1) racket.x = 1;
    if(racket.x + racket.w >= width) racket.x = width - 1 - racket.w;
}

int main(void){
    initscr();
    srand(time(NULL));
    raw();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    initRocket();
    moveBall(racket.x + racket.w / 2, racket.y - 1);
    initBall();
    int ballrun = 0;
    int running = 1;
    while(running){
        initWorld();
        putRacket();
        putBall();
        show();
        if(ball.iy >= height) {
            ballrun = 0;
            maxhitCount = (hitCount > maxhitCount) ? hitCount : maxhitCount;
            hitCount = 0;
            initBall();
        }
        if(ballrun) autoMoveBall();
        else moveBall(racket.x + racket.w / 2, racket.y - 1);

        int ch = getch();

        switch (ch){
        case 'a':
        case 'A':
        case KEY_LEFT:
            movePacket(racket.x - 2);
            break;
        case 'd':
        case 'D':
        case KEY_RIGHT:
            movePacket(racket.x + 2);
            break;
        case 'w':
        case 'W':
            ballrun = 1;
            break;
        case 'q':
        case 'Q':
            running = 0;
            break;
        }
        usleep(33000); 
        
    }

    endwin();
    return 0;
    
}