#include <gb/gb.h>
#include "ball.c"
#include "bar.c"

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

    move_sprite(0,128,128);

    move_sprite(1,20,50);
    move_sprite(2,20,58);
    move_sprite(3,20,66);
    move_sprite(4,20,74);

    move_sprite(5,56,50);
    move_sprite(6,56,58);
    move_sprite(7,56,66);
    move_sprite(8,56,74);
    SHOW_SPRITES;
}