#include <gb/gb.h>
#include <stdio.h>

#define L_BAR 1
#define R_BAR 5
#define TILE_SIZE 8

void ia_bar(WORD ball_x, WORD ball_y, WORD x_velocity, WORD y_velocity, WORD posicaotoporight, WORD posicaomeio1right, 
WORD posicaomeio2right, WORD posicaobaixoright, WORD RIGHT_LIMIT, WORD DOWN_LIMIT, WORD UP_LIMIT, WORD yr, WORD i)
{
  if (x_velocity < 0)
  { //bola indo p/ esquerda
    move_sprite(R_BAR, RIGHT_LIMIT, yr);
    move_sprite(R_BAR + 1, RIGHT_LIMIT, yr + TILE_SIZE);
    move_sprite(R_BAR + 2, RIGHT_LIMIT, yr + 2 * TILE_SIZE);
    move_sprite(R_BAR + 3, RIGHT_LIMIT, yr + 3 * TILE_SIZE);
    //salvando as posicoes da barra da direita
    posicaotoporight = yr;
    posicaomeio1right = yr + TILE_SIZE;
    posicaomeio2right = yr + 2 * TILE_SIZE;
    posicaobaixoright = yr + 3 * TILE_SIZE;
  }
  else
  { //bola indo p/ direita
    if (y_velocity > 0)
    { //bola indo p/ baixo

      if (ball_y > posicaomeio1right)
      {
	if (posicaobaixoright < DOWN_LIMIT)
        {
          posicaotoporight = yr + i;
          posicaomeio1right = yr + TILE_SIZE + i;
          posicaomeio2right = yr + 2 * TILE_SIZE + i;
          posicaobaixoright = yr + 3 * TILE_SIZE + i;
          yr += i;

          move_sprite(R_BAR, RIGHT_LIMIT, posicaotoporight);
          move_sprite(R_BAR + 1, RIGHT_LIMIT, posicaomeio1right);
          move_sprite(R_BAR + 2, RIGHT_LIMIT, posicaomeio2right);
          move_sprite(R_BAR + 3, RIGHT_LIMIT, posicaobaixoright);
        }else
        {
          return;
        }

      }
      if(ball_y <= posicaomeio1right)
      {
	 if (posicaotoporight > UP_LIMIT)
        {
          posicaotoporight = yr - i;
          posicaomeio1right = yr + TILE_SIZE - i;
          posicaomeio2right = yr + 2 * TILE_SIZE - i;
          posicaobaixoright = yr + 3 * TILE_SIZE - i;
          yr -= i;

          move_sprite(R_BAR, RIGHT_LIMIT, posicaotoporight);
          move_sprite(R_BAR + 1, RIGHT_LIMIT, posicaomeio1right);
          move_sprite(R_BAR + 2, RIGHT_LIMIT, posicaomeio2right);
          move_sprite(R_BAR + 3, RIGHT_LIMIT, posicaobaixoright);
        }else
        {
          return;
        }

      }
    }
    if (y_velocity < 0)
    { //bola indo p/ cima

      if (ball_y < posicaomeio1right)
      {
        if (posicaotoporight > UP_LIMIT){
        posicaotoporight = yr - i;
        posicaomeio1right = yr + TILE_SIZE - i;
        posicaomeio2right = yr + 2 * TILE_SIZE - i;
        posicaobaixoright = yr + 3 * TILE_SIZE - i;
        yr -= i;
        move_sprite(R_BAR, RIGHT_LIMIT, posicaotoporight);
        move_sprite(R_BAR + 1, RIGHT_LIMIT, posicaomeio1right);
        move_sprite(R_BAR + 2, RIGHT_LIMIT, posicaomeio2right);
        move_sprite(R_BAR + 3, RIGHT_LIMIT, posicaobaixoright);
        }else
        {
          return;
        }

      }
      if(ball_y >= posicaomeio1right)
      {
        if (posicaobaixoright < DOWN_LIMIT){
        posicaotoporight = yr + i;
        posicaomeio1right = yr + TILE_SIZE + i;
        posicaomeio2right = yr + 2 * TILE_SIZE + i;
        posicaobaixoright = yr + 3 * TILE_SIZE + i;
        yr += i;
        move_sprite(R_BAR, RIGHT_LIMIT, posicaotoporight);
        move_sprite(R_BAR + 1, RIGHT_LIMIT, posicaomeio1right);
        move_sprite(R_BAR + 2, RIGHT_LIMIT, posicaomeio2right);
        move_sprite(R_BAR + 3, RIGHT_LIMIT, posicaobaixoright);
        }else
        {
          return;
        }

      }
    }
    if (y_velocity == 0)
    {
      move_sprite(R_BAR, RIGHT_LIMIT, yr);
      move_sprite(R_BAR + 1, RIGHT_LIMIT, yr + TILE_SIZE);
      move_sprite(R_BAR + 2, RIGHT_LIMIT, yr + 2 * TILE_SIZE);
      move_sprite(R_BAR + 3, RIGHT_LIMIT, yr + 3 * TILE_SIZE);
      //salvando as posicoes da barra da direita
      posicaotoporight = yr;
      posicaomeio1right = yr + TILE_SIZE;
      posicaomeio2right = yr + 2 * TILE_SIZE;
      posicaobaixoright = yr + 3 * TILE_SIZE;
    }
  }
}		
