#include <gb/gb.h>

#define UP 0
#define DOWN 1
#define NONE 2
void seek(int ball_x,int ball_y,int bar_y,int difficulty){
    if(ball_x <= difficulty/4*SCREENWIDTH){
        if(bar_y > ball_y + 5)
            return UP;
        else if(bar_y < ball_y - 5)
            return DOWN;
        else
            return NONE;
    }
}