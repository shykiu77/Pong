#include <gb/gb.h>
#include "../assets/ball.c"
#include "../assets/bar.c"
#include "../assets/font.c"
#include "../assets/map.c"
#include "../assets/map2.c"
#include "../assets/gray.c"

#include <gb/drawing.h>
#include <stdio.h>
//#include <stdlib.h>  //uso da funcao rand

#define BALL 0
#define L_BAR 1
#define R_BAR 5

#define TILE_SIZE 8

WORD x_velocity;
WORD y_velocity;

WORD pad; //variavel para captar os inputs do gameboy
//WORD gameover = 1;

WORD yl = SCREENHEIGHT / 2 - TILE_SIZE; //y da barra da esquerda
WORD yr = SCREENHEIGHT / 2 - TILE_SIZE; //y da barra da direita

//propriedades da bola
WORD ball_x = SCREENWIDTH / 2;
WORD ball_y = SCREENHEIGHT / 2;

//propriedades da barra da esquerda
WORD posicaotopo = 0;
WORD posicaomeio1 = 0;
WORD posicaomeio2 = 0;
WORD posicaobaixo = 0;
WORD i = 2;      //velocidade de movimentacao barra da esquerda
WORD action = 3; //1 = barra p/ cima ; 0 = barra p/ baixo ; 3 = nenhuma acao

//propriedades da barra da direita
WORD posicaotoporight = 0;
WORD posicaomeio1right = 0;
WORD posicaomeio2right = 0;
WORD posicaobaixoright = 0;

//controle de reinicio da partida caso alguem pontue
WORD reinicia = 2; // 0 = false, 1 = true, 2 = null

//WORD difficulty = 2;  nao esta sendo utilizada ainda

WORD RADIUS_BALL = 4;

//players
WORD score_player = 0;
WORD score_computer = 0;

void update_ball()
{
  ball_x += x_velocity;
  ball_y += y_velocity;
  //if(ball_x >= SCREENWIDTH || ball_x <= 0){
  //   ball_x = (ball_x >=  SCREENWIDTH ? SCREENWIDTH : 0);
  //  x_velocity = - x_velocity;
  // }
  move_sprite(BALL, ball_x, ball_y);
}

void move_bar()
{
  if (posicaobaixo <= 0 && action == 0) //pad p/ baixo mas ja esta no limite inferior da tela
  {
    action = 3;
    return;
  }

  if (posicaobaixo > 0 && action == 0) //pad p/ baixo e nao esta no limite inferior da tela
  {
    posicaotopo = yl + i;
    posicaomeio1 = yl + TILE_SIZE + i;
    posicaomeio2 = yl + 2 * TILE_SIZE + i;
    posicaobaixo = yl + 3 * TILE_SIZE + i;
    yl += i;

    move_sprite(L_BAR, TILE_SIZE, posicaotopo);
    move_sprite(L_BAR + 1, TILE_SIZE, posicaomeio1);
    move_sprite(L_BAR + 2, TILE_SIZE, posicaomeio2);
    move_sprite(L_BAR + 3, TILE_SIZE, posicaobaixo);

    action = 3;
  }
  if (posicaotopo >= SCREENHEIGHT && action == 1) //pad p/ cima mas ja esta no limite superior da tela
  {
    action = 3;
    return;
  }

  if (posicaotopo < SCREENHEIGHT && action == 1) //pad p/ cima e nao esta no limite superior na tela
  {
    posicaotopo = yl - i;
    posicaomeio1 = yl + TILE_SIZE - i;
    posicaomeio2 = yl + 2 * TILE_SIZE - i;
    posicaobaixo = yl + 3 * TILE_SIZE - i;
    yl -= i;

    move_sprite(L_BAR, TILE_SIZE, posicaotopo);
    move_sprite(L_BAR + 1, TILE_SIZE, posicaomeio1);
    move_sprite(L_BAR + 2, TILE_SIZE, posicaomeio2);
    move_sprite(L_BAR + 3, TILE_SIZE, posicaobaixo);

    action = 3;
  }
}

void check_collision()
{
  // Bola toca na parede da IA
  if (ball_x >= SCREENWIDTH)
  {
    //score_player++;
    reinicia = 1;
    return;
  }

  // Bola toca na parede do jogador
  if (ball_x <= 0)
  {
    //score_computer++;
    reinicia = 1;
    return;
  }

  // Bola toca na parte superior ou inferior da tela
  if (ball_y - RADIUS_BALL <= 0 || ball_y + RADIUS_BALL >= SCREENHEIGHT)
  {
    y_velocity *= -1;
    return;
  }

  // Bola toca na barra esquerda
  if (ball_x - RADIUS_BALL == TILE_SIZE && ball_y >= yl - RADIUS_BALL && ball_y <= yl + 4 * TILE_SIZE + RADIUS_BALL)
  {
    x_velocity = -x_velocity;
    if (ball_y - yl < 8)
      y_velocity = -1;
    else if (ball_y - yl > 16)
      y_velocity = 1;
    else
      y_velocity = 0;
    return;
  }

  // Bola toca na barra direita
  if (ball_x + RADIUS_BALL == SCREENWIDTH && ball_y >= yr - RADIUS_BALL && ball_y <= yr + 4 * TILE_SIZE + RADIUS_BALL)
  {
    x_velocity = -x_velocity;
    if (ball_y - yr < 8)
      y_velocity = -1;
    else if (ball_y - yr > 16)
      y_velocity = 1;
    else
      y_velocity = 0;
    return;
  }
}

void ia_bar()
{
  if (x_velocity < 0)
  { //bola indo p/ esquerda

    move_sprite(R_BAR, SCREENWIDTH, yr);
    move_sprite(R_BAR + 1, SCREENWIDTH, yr + TILE_SIZE);
    move_sprite(R_BAR + 2, SCREENWIDTH, yr + 2 * TILE_SIZE);
    move_sprite(R_BAR + 3, SCREENWIDTH, yr + 3 * TILE_SIZE);
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
        posicaotoporight = yr + i;
        posicaomeio1right = yr + TILE_SIZE + i;
        posicaomeio2right = yr + 2 * TILE_SIZE + i;
        posicaobaixoright = yr + 3 * TILE_SIZE + i;
        yr += i;

        move_sprite(R_BAR, SCREENWIDTH, posicaotoporight);
        move_sprite(R_BAR + 1, SCREENWIDTH, posicaomeio1right);
        move_sprite(R_BAR + 2, SCREENWIDTH, posicaomeio2right);
        move_sprite(R_BAR + 3, SCREENWIDTH, posicaobaixoright);
      }
      else
      {
        posicaotoporight = yr - i;
        posicaomeio1right = yr + TILE_SIZE - i;
        posicaomeio2right = yr + 2 * TILE_SIZE - i;
        posicaobaixoright = yr + 3 * TILE_SIZE - i;
        yr -= i;

        move_sprite(R_BAR, SCREENWIDTH, posicaotoporight);
        move_sprite(R_BAR + 1, SCREENWIDTH, posicaomeio1right);
        move_sprite(R_BAR + 2, SCREENWIDTH, posicaomeio2right);
        move_sprite(R_BAR + 3, SCREENWIDTH, posicaobaixoright);
      }
    }
    if (y_velocity < 0)
    { //bola indo p/ cima

      if (ball_y < posicaomeio1right)
      {
        posicaotoporight = yr - i;
        posicaomeio1right = yr + TILE_SIZE - i;
        posicaomeio2right = yr + 2 * TILE_SIZE - i;
        posicaobaixoright = yr + 3 * TILE_SIZE - i;
        yr -= i;

        move_sprite(R_BAR, SCREENWIDTH, posicaotoporight);
        move_sprite(R_BAR + 1, SCREENWIDTH, posicaomeio1right);
        move_sprite(R_BAR + 2, SCREENWIDTH, posicaomeio2right);
        move_sprite(R_BAR + 3, SCREENWIDTH, posicaobaixoright);
      }
      else
      {
        posicaotoporight = yr + i;
        posicaomeio1right = yr + TILE_SIZE + i;
        posicaomeio2right = yr + 2 * TILE_SIZE + i;
        posicaobaixoright = yr + 3 * TILE_SIZE + i;
        yr += i;

        move_sprite(R_BAR, SCREENWIDTH, posicaotoporight);
        move_sprite(R_BAR + 1, SCREENWIDTH, posicaomeio1right);
        move_sprite(R_BAR + 2, SCREENWIDTH, posicaomeio2right);
        move_sprite(R_BAR + 3, SCREENWIDTH, posicaobaixoright);
      }
    }
    if (y_velocity == 0)
    {
      move_sprite(R_BAR, SCREENWIDTH, yr);
      move_sprite(R_BAR + 1, SCREENWIDTH, yr + TILE_SIZE);
      move_sprite(R_BAR + 2, SCREENWIDTH, yr + 2 * TILE_SIZE);
      move_sprite(R_BAR + 3, SCREENWIDTH, yr + 3 * TILE_SIZE);
      //salvando as posicoes da barra da direita
      posicaotoporight = yr;
      posicaomeio1right = yr + TILE_SIZE;
      posicaomeio2right = yr + 2 * TILE_SIZE;
      posicaobaixoright = yr + 3 * TILE_SIZE;
    }
  }
}

void set_props()
{

  ball_x = SCREENWIDTH / 2;
  ball_y = SCREENHEIGHT / 2;
  update_ball();

  move_sprite(L_BAR, TILE_SIZE, yl);
  move_sprite(L_BAR + 1, TILE_SIZE, yl + TILE_SIZE);
  move_sprite(L_BAR + 2, TILE_SIZE, yl + 2 * TILE_SIZE);
  move_sprite(L_BAR + 3, TILE_SIZE, yl + 3 * TILE_SIZE);
  //salvando as posicoes da barra da esquerda
  posicaotopo = yl;
  posicaomeio1 = yl + TILE_SIZE;
  posicaomeio2 = yl + 2 * TILE_SIZE;
  posicaobaixo = yl + 3 * TILE_SIZE;

  move_sprite(R_BAR, SCREENWIDTH, yr);
  move_sprite(R_BAR + 1, SCREENWIDTH, yr + TILE_SIZE);
  move_sprite(R_BAR + 2, SCREENWIDTH, yr + 2 * TILE_SIZE);
  move_sprite(R_BAR + 3, SCREENWIDTH, yr + 3 * TILE_SIZE);
  //salvando as posicoes da barra da direita
  posicaotoporight = yr;
  posicaomeio1right = yr + TILE_SIZE;
  posicaomeio2right = yr + 2 * TILE_SIZE;
  posicaobaixoright = yr + 3 * TILE_SIZE;
}
void hide(int sprite)
{
  move_sprite(sprite, -10, -10);
}

void loadMenu()
{
}

void main()
{
  set_bkg_data(0, 6, font);

  set_bkg_tiles(0, 0, 20, 18, map);
  SHOW_BKG;

  int start = FALSE;
  while (!start)
  {
    pad = joypad();
    if (pad)
      start = TRUE;
  }
  set_bkg_data(0, 1, gray);
  set_bkg_tiles(0, 0, 20, 18, map2);
  SHOW_BKG;
  SPRITES_8x8;
  set_sprite_data(0, 1, ball);
  set_sprite_data(1, 1, bar);
  set_sprite_data(2, 1, bar);
  set_sprite_data(3, 1, bar);
  set_sprite_data(4, 1, bar);
  set_sprite_data(5, 1, bar);
  set_sprite_data(6, 1, bar);
  set_sprite_data(7, 1, bar);
  set_sprite_data(8, 1, bar);

  set_sprite_tile(0, 0);
  set_sprite_tile(1, 1);
  set_sprite_tile(2, 2);
  set_sprite_tile(3, 3);
  set_sprite_tile(4, 4);
  set_sprite_tile(5, 5);
  set_sprite_tile(6, 6);
  set_sprite_tile(7, 7);
  set_sprite_tile(8, 8);

  set_props();

  SHOW_SPRITES;
  while (1)
  {
    if (reinicia == 1)
    { //quando o jogo reiniciar por pontuação
      yl = SCREENHEIGHT / 2 - TILE_SIZE;
      yr = SCREENHEIGHT / 2 - TILE_SIZE;
      set_props();
      //randomizacao removida momentaneamente
      x_velocity = 2;
      y_velocity = 0;
      reinicia = 0;
    }
    if (reinicia == 2)
    { //quando o jogo roda a primeira vez
      x_velocity = 2;
      y_velocity = 0;
      reinicia = 0;
    }
    pad = joypad();
    if (pad & J_UP)
    {
      action = 1;
      move_bar();
    }
    if (pad & J_DOWN)
    {
      action = 0;
      move_bar();
    }
    ia_bar();
    check_collision();

    wait_vbl_done();
    delay(20);
    update_ball();
    //gameover = 0;
  }
}