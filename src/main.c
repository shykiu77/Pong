#include <gb/gb.h>
#include "../assets/ball.c"
#include "../assets/bar.c"
#include "../assets/font.c"
#include "../assets/map.c"
#include "../assets/map2.c"
#include "../assets/gray.c"

#include <gb/drawing.h>
#include <stdio.h>

#define BALL 0
#define L_BAR 1
#define R_BAR 5

#define TILE_SIZE 8

WORD x_velocity = 2;
WORD y_velocity = 0;

WORD pad;
WORD gameover = 1;
WORD i = 1;
WORD y = SCREENHEIGHT/2 - TILE_SIZE;

//propriedades da bola
WORD ball_x = SCREENWIDTH/2;
WORD ball_y = SCREENHEIGHT/2;
WORD ball_dx = 1;
WORD ball_dy = 1;


WORD action = 3;

WORD difficulty = 2;
void update_ball(){
    ball_x += x_velocity;
    ball_y += y_velocity;
    if(ball_x >= SCREENWIDTH || ball_x <= 0){
        ball_x = (ball_x >=  SCREENWIDTH ? SCREENWIDTH : 0);
        x_velocity = - x_velocity;
    }
    move_sprite(BALL,ball_x,ball_y);
}

void move_bar() {

	// if the up arrow is pressed move paddle up
	if (action == 1) {

	    move_sprite(L_BAR,TILE_SIZE,y-i);
        move_sprite(L_BAR+1,TILE_SIZE,y + TILE_SIZE-i);
        move_sprite(L_BAR+2,TILE_SIZE,y + 2*TILE_SIZE-i);
        move_sprite(L_BAR+3,TILE_SIZE,y + 3*TILE_SIZE-i);
        y -= i;
        action = 3;
	}
    if (action == 0) {

	    move_sprite(L_BAR,TILE_SIZE,y+i);
        move_sprite(L_BAR+1,TILE_SIZE,y + TILE_SIZE+i);
        move_sprite(L_BAR+2,TILE_SIZE,y + 2*TILE_SIZE+i);
        move_sprite(L_BAR+3,TILE_SIZE,y + 3*TILE_SIZE+i);
        y+= i;
        action = 3;
	}
}



void set_props(){
    ball_x = SCREENWIDTH/2;
    ball_y = SCREENHEIGHT/2;
    update_ball();

    move_sprite(L_BAR,TILE_SIZE,SCREENHEIGHT/2 - TILE_SIZE);
    move_sprite(L_BAR+1,TILE_SIZE,SCREENHEIGHT/2 - TILE_SIZE + TILE_SIZE);
    move_sprite(L_BAR+2,TILE_SIZE,SCREENHEIGHT/2 - TILE_SIZE + 2*TILE_SIZE);
    move_sprite(L_BAR+3,TILE_SIZE,SCREENHEIGHT/2 - TILE_SIZE + 3*TILE_SIZE);

    move_sprite(R_BAR,SCREENWIDTH,SCREENHEIGHT/2 - TILE_SIZE);
    move_sprite(R_BAR+1,SCREENWIDTH,SCREENHEIGHT/2 - TILE_SIZE + TILE_SIZE);
    move_sprite(R_BAR+2,SCREENWIDTH,SCREENHEIGHT/2 - TILE_SIZE + 2*TILE_SIZE);
    move_sprite(R_BAR+3,SCREENWIDTH,SCREENHEIGHT/2 - TILE_SIZE + 3*TILE_SIZE);
}
void hide(int sprite){
    move_sprite(sprite,-10,-10);
}

void loadMenu(){
    
}


void main(){
    set_bkg_data(0,6,font);
    
    set_bkg_tiles(0,0,20,18,map);
    SHOW_BKG;

    int start = FALSE;
    while(!start){
        pad = joypad();
        if(pad)
            start = TRUE;
    }
    set_bkg_data(0,1,gray);
    set_bkg_tiles(0,0,20,18,map2);
    SHOW_BKG;
    SPRITES_8x8;
    set_sprite_data(0,1,ball);
    set_sprite_data(1,1,bar);
    set_sprite_data(2,1,bar);
    set_sprite_data(3,1,bar);
    set_sprite_data(4,1,bar);
    set_sprite_data(5,1,bar);
    set_sprite_data(6,1,bar);
    set_sprite_data(7,1,bar);
    set_sprite_data(8,1,bar);

    set_sprite_tile(0,0);
    set_sprite_tile(1,1);
    set_sprite_tile(2,2);
    set_sprite_tile(3,3);
    set_sprite_tile(4,4);
    set_sprite_tile(5,5);
    set_sprite_tile(6,6);
    set_sprite_tile(7,7);
    set_sprite_tile(8,8);

    set_props();
   
    SHOW_SPRITES;
    while(1){
        pad = joypad();
        if (pad & J_UP){
            action = 1;
            move_bar();
        }
        if (pad & J_DOWN){
            action = 0;
            move_bar();
        }
        
        wait_vbl_done();
        delay(20);
        //drawUI();
        update_ball();
        //gameover = 0;
        
    }
}