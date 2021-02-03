#include <gb/gb.h>
#include "../assets/ball.c"
#include "../assets/bar.c"
#include "../assets/font.c"
#include "../assets/map.c"
#include "../assets/map2.c"
#include "../assets/gray.c"
#include "../assets/score.c"
#include "./multiplayer.c"
#include "./ia.c"
#include <gb/drawing.h>
#include <stdio.h>
//#include <stdlib.h>  //uso da funcao rand

#define BALL 0
#define L_BAR 1
#define R_BAR 5

#define L_SCORE 9
#define R_SCORE 15

#define TILE_SIZE 8

WORD x_velocity = 0;
WORD y_velocity = 0;

WORD pad; //variavel para captar os inputs do gameboy
//WORD gameover = 1;

WORD yl = SCREENHEIGHT / 2 - TILE_SIZE; //y da barra da esquerda
WORD yr = SCREENHEIGHT / 2 - TILE_SIZE; //y da barra da direita

//propriedades da bola
WORD ball_x = SCREENWIDTH / 2;
WORD ball_y = SCREENHEIGHT / 2;

WORD i = 2; //velocidade de movimentacao das duas barras

//controle de reinicio da partida caso alguem pontue
WORD reinicia = 2; // 0 = false, 1 = true, 2 = null

//WORD difficulty = 2;  nao esta sendo utilizada ainda

WORD RADIUS_BALL = 4;

//players
WORD score_left = 0;
WORD score_right = 0;

WORD LEFT_LIMIT = 2 * TILE_SIZE;
WORD RIGHT_LIMIT = 19 * TILE_SIZE;
WORD UP_LIMIT = 4 * TILE_SIZE;
WORD DOWN_LIMIT = 18 * TILE_SIZE;

WORD fix = 2;

void update_ball()
{
  ball_x += x_velocity;
  ball_y += y_velocity;
  move_sprite(BALL, ball_x, ball_y);
}

void hide(int sprite)
{
  move_sprite(sprite, -10, -10);
}

void set_ball()
{
  move_sprite(BALL, ball_x, ball_y);
}
void set_bars()
{
  int posicaotopo, posicaomeio1, posicaomeio2, posicaobaixo, sprite, lado;
  posicaotopo = yl;
  posicaomeio1 = yl + TILE_SIZE;
  posicaomeio2 = yl + 2 * TILE_SIZE;
  posicaobaixo = yl + 3 * TILE_SIZE;
  sprite = L_BAR;
  lado = LEFT_LIMIT;
  move_sprite(sprite, lado, posicaotopo);
  move_sprite(sprite + 1, lado, posicaomeio1);
  move_sprite(sprite + 2, lado, posicaomeio2);
  move_sprite(sprite + 3, lado, posicaobaixo);

  posicaotopo = yr;
  posicaomeio1 = yr + TILE_SIZE;
  posicaomeio2 = yr + 2 * TILE_SIZE;
  posicaobaixo = yr + 3 * TILE_SIZE;
  sprite = R_BAR;
  lado = RIGHT_LIMIT;
  move_sprite(sprite, lado, posicaotopo);
  move_sprite(sprite + 1, lado, posicaomeio1);
  move_sprite(sprite + 2, lado, posicaomeio2);
  move_sprite(sprite + 3, lado, posicaobaixo);
}
void hide_score()
{
  for (int i = 0; i < 5; i++)
  {
    hide(L_SCORE + i);
    hide(R_SCORE + i);
  }
}
void set_scores()
{
  hide_score();
  move_sprite(L_SCORE + score_left, 3 * TILE_SIZE, 2 * TILE_SIZE);
  move_sprite(R_SCORE + score_right, 17 * TILE_SIZE, 2 * TILE_SIZE);
}

void mark_score_left()
{
  hide(L_SCORE + score_left - 1);
  move_sprite(L_SCORE + score_left, 3 * TILE_SIZE, 2 * TILE_SIZE);
}
void mark_score_right()
{
  hide(R_SCORE + score_right - 1);
  move_sprite(R_SCORE + score_right, 17 * TILE_SIZE, 2 * TILE_SIZE);
}
//L_or_R: 0 = left, 1 = right.
//action: 1 = barra para cima ; 0 = barra para baixo ; 3 = nenhuma ação.
void move_bar(int L_or_R, int action)
{
  int posicaotopo, posicaomeio1, posicaomeio2, posicaobaixo, sprite, lado;
  if (L_or_R == 0)
  {
    posicaotopo = yl;
    posicaomeio1 = yl + TILE_SIZE;
    posicaomeio2 = yl + 2 * TILE_SIZE;
    posicaobaixo = yl + 3 * TILE_SIZE;
    sprite = L_BAR;
    lado = LEFT_LIMIT;
  }
  else
  {
    posicaotopo = yr;
    posicaomeio1 = yr + TILE_SIZE;
    posicaomeio2 = yr + 2 * TILE_SIZE;
    posicaobaixo = yr + 3 * TILE_SIZE;
    sprite = R_BAR;
    lado = RIGHT_LIMIT;
  }
  if (posicaobaixo >= DOWN_LIMIT && action == 0) //pad p/ baixo mas ja esta no limite inferior da tela
  {
    action = 3;
    return;
  }

  if (posicaobaixo < DOWN_LIMIT && action == 0) //pad p/ baixo e nao esta no limite inferior da tela
  {
    posicaotopo += i;
    posicaomeio1 += i;
    posicaomeio2 += i;
    posicaobaixo += i;
    if (L_or_R == 0)
      yl += i;
    else
      yr += i;

    move_sprite(sprite, lado, posicaotopo);
    move_sprite(sprite + 1, lado, posicaomeio1);
    move_sprite(sprite + 2, lado, posicaomeio2);
    move_sprite(sprite + 3, lado, posicaobaixo);

    action = 3;
  }
  if (posicaotopo <= UP_LIMIT && action == 1) //pad p/ cima mas ja esta no limite superior da tela
  {
    action = 3;
    return;
  }

  if (posicaotopo > UP_LIMIT && action == 1) //pad p/ cima e nao esta no limite superior na tela
  {
    posicaotopo += -i;
    posicaomeio1 += -i;
    posicaomeio2 += -i;
    posicaobaixo += -i;
    if (L_or_R == 0)
      yl += -i;
    else
      yr += -i;

    move_sprite(sprite, lado, posicaotopo);
    move_sprite(sprite + 1, lado, posicaomeio1);
    move_sprite(sprite + 2, lado, posicaomeio2);
    move_sprite(sprite + 3, lado, posicaobaixo);

    action = 3;
  }
}

void check_collision()
{
  //por algum motivo a velocidade x ganha um valor aleatório na primeira iteração do loop, esse fix serve para evitar que um ponto seja marcado equivocadamente.
  if (fix >= 0)
    fix--;
  // Bola toca na parede da IA
  if (ball_x >= RIGHT_LIMIT)
  {
    if (fix < 0)
    {
      NR51_REG = 0x01;
      NR10_REG = 0X00;
      NR11_REG = 0X81;
      NR12_REG = 0X43;
      NR13_REG = 0XDB;
      NR14_REG = 0X86;
      score_left++;
      mark_score_left();
      delay(300);
    }
    reinicia = 1;
    return;
  }

  // Bola toca na parede do jogador
  if (ball_x <= LEFT_LIMIT)
  {

    if (fix < 0)
    {
      NR51_REG = 0x10;
      NR10_REG = 0X00;
      NR11_REG = 0X81;
      NR12_REG = 0X43;
      NR13_REG = 0XDB;
      NR14_REG = 0X86;
      score_right++;
      mark_score_right();
      delay(300);
    }
    else
      fix--;
    reinicia = 1;
    return;
  }

  // Bola toca na parte superior ou inferior da tela
  if (ball_y <= UP_LIMIT || ball_y >= DOWN_LIMIT)
  {
    NR51_REG = 0x11;
    NR10_REG = 0X00;
    NR11_REG = 0X81;
    NR12_REG = 0X43;
    NR13_REG = 0XF2;
    NR14_REG = 0X85;
    y_velocity *= -1;
    return;
  }

  // Bola toca na barra esquerda
  if (ball_x - RADIUS_BALL <= LEFT_LIMIT && ball_y >= yl - RADIUS_BALL && ball_y <= yl + 4 * TILE_SIZE + RADIUS_BALL)
  {
    x_velocity = -x_velocity;
    NR51_REG = 0x10;
    NR10_REG = 0X00;
    NR11_REG = 0X81;
    NR12_REG = 0X43;
    NR13_REG = 0XF2;
    NR14_REG = 0X85;
    if (ball_y - yl < 4)
      y_velocity = -1;
    else if (ball_y - yl > 20)
    {
      y_velocity = 1;
    }
    else
    {
      y_velocity = 0;
    }
    return;
  }

  // Bola toca na barra direita
  if (ball_x + RADIUS_BALL >= RIGHT_LIMIT && ball_y >= yr - RADIUS_BALL && ball_y <= yr + 4 * TILE_SIZE + RADIUS_BALL)
  {
    x_velocity = -x_velocity;

    NR51_REG = 0x01;
    NR10_REG = 0X00;
    NR11_REG = 0X81;
    NR12_REG = 0X43;
    NR13_REG = 0XF2;
    NR14_REG = 0X85;
    if (ball_y - yr < 4)
      y_velocity = -1;
    else if (ball_y - yr > 20)
    {
      y_velocity = 1;
    }
    else
    {
      y_velocity = 0;
    }
    return;
  }
}

void set_props()
{

  ball_x = SCREENWIDTH / 2;
  ball_y = SCREENHEIGHT / 2;
  update_ball();

  move_sprite(L_BAR, LEFT_LIMIT, yl);
  move_sprite(L_BAR + 1, LEFT_LIMIT, yl + TILE_SIZE);
  move_sprite(L_BAR + 2, LEFT_LIMIT, yl + 2 * TILE_SIZE);
  move_sprite(L_BAR + 3, LEFT_LIMIT, yl + 3 * TILE_SIZE);

  move_sprite(R_BAR, RIGHT_LIMIT, yr);
  move_sprite(R_BAR + 1, RIGHT_LIMIT, yr + TILE_SIZE);
  move_sprite(R_BAR + 2, RIGHT_LIMIT, yr + 2 * TILE_SIZE);
  move_sprite(R_BAR + 3, RIGHT_LIMIT, yr + 3 * TILE_SIZE);
}

void loadMenu()
{
}

void main()
{

  set_bkg_data(0, 6, font);

  set_bkg_tiles(0, 0, 20, 18, map);
  SHOW_BKG;

  int side = wait_for_connection();

  set_bkg_data(0, 14, gray);
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

  set_sprite_data(9, 6, Score);
  set_sprite_data(15, 6, Score);

  for (int i = 0; i <= 20; i++)
    set_sprite_tile(i, i);

  set_props();
  move_sprite(L_SCORE, 3 * TILE_SIZE, 2 * TILE_SIZE);
  move_sprite(R_SCORE, 17 * TILE_SIZE, 2 * TILE_SIZE);

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

    if (side == 0)
    {
      //espera ver o que o b faz
      //funcao receive data
      receive_byte();
      while (_io_status == IO_RECEIVING)
      {
        ;
      }
      int action = _io_in;
      //NR52_REG = 0x80;  //habilita o som
      //NR50_REG = 0x77; //volume no maximo
      //NR51_REG = 0x11;  //som na esqueda
      //NR50_REG = 0x77;  //som da direita

      pad = joypad();

      if (pad & J_UP)
      {
        move_bar(side, 1);
      }
      if (pad & J_DOWN)
      {
        move_bar(side, 0);
      }
      move_bar(!side, action);

      update_ball();
      check_collision();
      int data[6];
      data[0] = ball_x;
      data[1] = ball_y;
      data[2] = yl;
      data[3] = yr;
      data[4] = score_left;
      data[5] = score_right;
      send_data(data, 6);
      //senddata  //ball_x , ball_y, yl, yr , scorel, scorer
      wait_vbl_done();
      //gameover = 0;
    }
    else
    {
      pad = joypad();

      if (pad & J_UP)
      {
        send_action(1);
      }
      else if (pad & J_DOWN)
      {
        send_action(0);
      }
      else
      {
        send_action(3);
      }
      int datarecieve[6];
      recieve_data(datarecieve, 6);
      ball_x = datarecieve[0];
      ball_y = datarecieve[1];
      yl = datarecieve[2];
      yr = datarecieve[3];
      score_left = datarecieve[4];
      score_right = datarecieve[5];
      set_scores();
      set_bars();
      set_ball();
    }
  }
}
