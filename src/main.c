#include <gb/gb.h>
#include "ball.c"
#include "bar.c"

#define BALL 0
#define L_BAR 1
#define R_BAR 5

#define TILE_SIZE 8

void set_props(){
    move_sprite(BALL,SCREENWIDTH/2,SCREENHEIGHT/2);

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

void main(){
    SPRITES_8x8;
    set_sprite_data(0,0,ball);
    set_sprite_data(1,0,bar);
    set_sprite_data(2,0,bar);
    set_sprite_data(3,0,bar);
    set_sprite_data(4,0,bar);
    set_sprite_data(5,0,bar);
    set_sprite_data(6,0,bar);
    set_sprite_data(7,0,bar);
    set_sprite_data(8,0,bar);

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
    hide(BALL);
    SHOW_SPRITES;
}