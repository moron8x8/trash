#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char getch(void) {
    struct termios old, new;
    char ch;
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return ch;
}

int main (void) {
    srand(time(NULL));

    char world [9][29];
    int y = 4;
    int x = 14;
    int x0, y0;
    int xstar, ystar;
    xstar = rand() % 27 + 1;
    ystar = rand() % 7 + 1;
    int score = 0; 

    char key;

    do{
        system("clear");
        for (int row = 0; row < 9; row++){
            for (int col = 0; col < 29; col++){
                if(row == 0 || row == 8 || col == 0 || col == 28){
                    world [row][col] = '#';
                }else{
                    world [row][col] = ' ';
                }
            }
        }
        world [y][x] = '@';
        world [ystar][xstar] = '*';
        for (int row = 0; row < 9; row++){
            for (int col = 0; col < 29; col++){
                printf("%c", world [row][col]);
            }
            printf("\n");
        }
        printf("Score: %d\n", score);
        key = getch();
        
        x0 = x;
        y0 = y;
        if (key == 'w') y--;
        if (key == 's') y++;
        if (key == 'a') x--;
        if (key == 'd') x++;
        if (world[y][x] == '#'){
            x = x0;
            y = y0;
        }
        if (x == xstar && y == ystar){
            xstar = rand() % 27 + 1;
            ystar = rand() % 7 + 1;
            score ++;
        }

    }while(key != 'e');




    return 0;
}
