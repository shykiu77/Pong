#include <gb/gb.h>
#include "../assets/ball.c"
#include "../assets/bar.c"
#include "../assets/font.c"
#include "../assets/map.c"
#include "../assets/map2.c"
#include "../assets/gray.c"
#include "../assets/score.c"

#include <gb/drawing.h>
#include <stdio.h>
//#include <stdlib.h>  //uso da funcao rand

#define BALL 0
#define L_BAR 1
#define R_BAR 5

#define L_SCORE 9
#define R_SCORE 15

#define TILE_SIZE 8

WORD x_velocity=0;
WORD y_velocity=0;

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

WORD action = 3; //1 = barra p/ cima ; 0 = barra p/ baixo ; 3 = nenhuma acao
WORD i = 1;      //velocidade de movimentacao das duas barras

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

WORD LEFT_LIMIT = 2*TILE_SIZE;
WORD RIGHT_LIMIT = 19*TILE_SIZE;
WORD UP_LIMIT = 4*TILE_SIZE;
WORD DOWN_LIMIT = 18*TILE_SIZE;

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

void mark_score_player(){
  hide(L_SCORE+score_player-1);
  move_sprite(L_SCORE+score_player,3*TILE_SIZE,2*TILE_SIZE);
}
void mark_score_computer(){
  hide(R_SCORE+score_computer-1);
  move_sprite(R_SCORE+score_computer,17*TILE_SIZE,2*TILE_SIZE);
}
void move_bar()
{
  if (posicaobaixo >= DOWN_LIMIT && action == 0) //pad p/ baixo mas ja esta no limite inferior da tela
  {
    action = 3;
    return;
  }

  if (posicaobaixo < DOWN_LIMIT && action == 0) //pad p/ baixo e nao esta no limite inferior da tela
  {
    posicaotopo = yl + i;
    posicaomeio1 = yl + TILE_SIZE + i;
    posicaomeio2 = yl + 2 * TILE_SIZE + i;
    posicaobaixo = yl + 3 * TILE_SIZE + i;
    yl += i;

    move_sprite(L_BAR, LEFT_LIMIT, posicaotopo);
    move_sprite(L_BAR + 1, LEFT_LIMIT, posicaomeio1);
    move_sprite(L_BAR + 2, LEFT_LIMIT, posicaomeio2);
    move_sprite(L_BAR + 3, LEFT_LIMIT, posicaobaixo);

    action = 3;
  }
  if (posicaotopo <= UP_LIMIT && action == 1) //pad p/ cima mas ja esta no limite superior da tela
  {
    action = 3;
    return;
  }

  if (posicaotopo  > UP_LIMIT && action == 1) //pad p/ cima e nao esta no limite superior na tela
  {
    posicaotopo = yl - i;
    posicaomeio1 = yl + TILE_SIZE - i;
    posicaomeio2 = yl + 2 * TILE_SIZE - i;
    posicaobaixo = yl + 3 * TILE_SIZE - i;
    yl -= i;

    move_sprite(L_BAR, LEFT_LIMIT, posicaotopo);
    move_sprite(L_BAR + 1, LEFT_LIMIT, posicaomeio1);
    move_sprite(L_BAR + 2, LEFT_LIMIT, posicaomeio2);
    move_sprite(L_BAR + 3, LEFT_LIMIT, posicaobaixo);

    action = 3;
  }
}

void check_collision()
{
  //por algum motivo a velocidade x ganha um valor aleatório na primeira iteração do loop, esse fix serve para evitar que um ponto seja marcado equivocadamente.
  if(fix >= 0)
    fix--;
  // Bola toca na parede da IA
  if (ball_x >= RIGHT_LIMIT)
  {
    score_player++;
    if(fix < 0)
      mark_score_player();
    reinicia = 1;
    return;
  }

  // Bola toca na parede do jogador
  if (ball_x <= LEFT_LIMIT)
  {
    score_computer++;
    if(fix < 0)
      mark_score_computer();
    else 
      fix--;
    reinicia = 1;
    return;
  }

  // Bola toca na parte superior ou inferior da tela
  if (ball_y <= UP_LIMIT || ball_y >= DOWN_LIMIT)
  {
    y_velocity *= -1;
    return;
  }

  // Bola toca na barra esquerda
  if (ball_x - RADIUS_BALL <= LEFT_LIMIT && ball_y >= yl - RADIUS_BALL && ball_y <= yl + 4 * TILE_SIZE + RADIUS_BALL)
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
  if (ball_x + RADIUS_BALL >= RIGHT_LIMIT && ball_y >= yr - RADIUS_BALL && ball_y <= yr + 4 * TILE_SIZE + RADIUS_BALL)
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

void set_props()
{

  ball_x = SCREENWIDTH / 2;
  ball_y = SCREENHEIGHT / 2;
  update_ball();

  move_sprite(L_BAR, LEFT_LIMIT, yl);
  move_sprite(L_BAR + 1, LEFT_LIMIT, yl + TILE_SIZE);
  move_sprite(L_BAR + 2, LEFT_LIMIT, yl + 2 * TILE_SIZE);
  move_sprite(L_BAR + 3, LEFT_LIMIT, yl + 3 * TILE_SIZE);
  //salvando as posicoes da barra da esquerda
  posicaotopo = yl;
  posicaomeio1 = yl + TILE_SIZE;
  posicaomeio2 = yl + 2 * TILE_SIZE;
  posicaobaixo = yl + 3 * TILE_SIZE;

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

  set_sprite_data(9,6,Score);
  set_sprite_data(15,6,Score);


  for(int i=0;i<=20;i++)
    set_sprite_tile(i,i);
  
  set_props();
  move_sprite(L_SCORE,3*TILE_SIZE,2*TILE_SIZE);
  move_sprite(R_SCORE,17*TILE_SIZE,2*TILE_SIZE);

  SHOW_SPRITES;
  while (1)
  {
    if(score_player== 5 || score_computer == 5){
      
    }
    else{
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

      update_ball();
      check_collision();

      wait_vbl_done();
      delay(20);
      //gameover = 0;
    }
  }
}