;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.4 #11952 (MINGW64)
;--------------------------------------------------------
	.module main
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _set_sprite_data
	.globl _set_bkg_tiles
	.globl _set_bkg_data
	.globl _wait_vbl_done
	.globl _joypad
	.globl _rand
	.globl _initrand
	.globl _randomBkgTiles
	.globl _lastKeys
	.globl _eY
	.globl _eX
	.globl _playerY
	.globl _playerX
	.globl _j
	.globl _i
	.globl _myBkgData
	.globl _sprites
	.globl _initGame
	.globl _updatePlayer
	.globl _collisionCheck
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_i::
	.ds 1
_j::
	.ds 1
_playerX::
	.ds 1
_playerY::
	.ds 1
_eX::
	.ds 10
_eY::
	.ds 10
_lastKeys::
	.ds 1
_randomBkgTiles::
	.ds 20
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;..\src\main.c:43: void main(){
;	---------------------------------
; Function main
; ---------------------------------
_main::
;..\src\main.c:45: initGame();																	// RAN ONCE AT STARTUP
	call	_initGame
;..\src\main.c:49: while(1){
00102$:
;..\src\main.c:51: updatePlayer();															// UPDATE PLAYER
	call	_updatePlayer
;..\src\main.c:53: HIDE_WIN;																// SHOW WINDOW LAYER
	ldh	a, (_LCDC_REG+0)
	and	a, #0xdf
	ldh	(_LCDC_REG+0),a
;..\src\main.c:54: SHOW_SPRITES;															// HIDE SPRITES LAYER
	ldh	a, (_LCDC_REG+0)
	or	a, #0x02
	ldh	(_LCDC_REG+0),a
;..\src\main.c:55: SHOW_BKG;																// SHOW BACKGROUND LAYER
	ldh	a, (_LCDC_REG+0)
	or	a, #0x01
	ldh	(_LCDC_REG+0),a
;..\src\main.c:57: lastKeys = joypad();													// UPDATE OUR KEYPRESSES
	call	_joypad
	ld	hl, #_lastKeys
	ld	(hl), e
;..\src\main.c:58: wait_vbl_done();														// WAIT FOR VBLANK TO FINISH - ENSURES 60 FRAMES PER SECOND MAXIMUM
	call	_wait_vbl_done
;..\src\main.c:63: }
	jr	00102$
_sprites:
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x42	; 66	'B'
	.db #0x42	; 66	'B'
	.db #0xa9	; 169
	.db #0xa9	; 169
	.db #0xa9	; 169
	.db #0xa9	; 169
	.db #0x81	; 129
	.db #0x81	; 129
	.db #0x91	; 145
	.db #0x91	; 145
	.db #0x42	; 66	'B'
	.db #0x42	; 66	'B'
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x42	; 66	'B'
	.db #0x42	; 66	'B'
	.db #0x81	; 129
	.db #0x81	; 129
	.db #0xed	; 237
	.db #0xed	; 237
	.db #0x81	; 129
	.db #0x81	; 129
	.db #0x91	; 145
	.db #0x91	; 145
	.db #0x42	; 66	'B'
	.db #0x42	; 66	'B'
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x99	; 153
	.db #0x81	; 129
	.db #0x42	; 66	'B'
	.db #0x5a	; 90	'Z'
	.db #0x24	; 36
	.db #0x3c	; 60
	.db #0x99	; 153
	.db #0x7e	; 126
	.db #0x99	; 153
	.db #0x7e	; 126
	.db #0x24	; 36
	.db #0x3c	; 60
	.db #0x42	; 66	'B'
	.db #0x5a	; 90	'Z'
	.db #0x99	; 153
	.db #0x81	; 129
	.db #0x38	; 56	'8'
	.db #0x04	; 4
	.db #0x7c	; 124
	.db #0x02	; 2
	.db #0x5c	; 92
	.db #0x22	; 34
	.db #0x5c	; 92
	.db #0x22	; 34
	.db #0x5c	; 92
	.db #0x22	; 34
	.db #0x5c	; 92
	.db #0x22	; 34
	.db #0x7c	; 124
	.db #0x02	; 2
	.db #0x38	; 56	'8'
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x1c	; 28
	.db #0x1c	; 28
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x6c	; 108	'l'
	.db #0x6c	; 108	'l'
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x7f	; 127
	.db #0x7f	; 127
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x1e	; 30
	.db #0x1e	; 30
	.db #0x70	; 112	'p'
	.db #0x70	; 112	'p'
	.db #0x7f	; 127
	.db #0x7f	; 127
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x7f	; 127
	.db #0x7f	; 127
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x43	; 67	'C'
	.db #0x43	; 67	'C'
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x60	; 96
	.db #0x6c	; 108	'l'
	.db #0x6c	; 108	'l'
	.db #0x6c	; 108	'l'
	.db #0x6c	; 108	'l'
	.db #0x7f	; 127
	.db #0x7f	; 127
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x7f	; 127
	.db #0x7f	; 127
	.db #0x60	; 96
	.db #0x60	; 96
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x60	; 96
	.db #0x60	; 96
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x7f	; 127
	.db #0x7f	; 127
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x18	; 24
	.db #0x18	; 24
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x3e	; 62
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x63	; 99	'c'
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x00	; 0
_myBkgData:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x36	; 54	'6'
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x50	; 80	'P'
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x0e	; 14
	.db #0x00	; 0
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x50	; 80	'P'
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x50	; 80	'P'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
;..\src\main.c:69: void initGame(){
;	---------------------------------
; Function initGame
; ---------------------------------
_initGame::
;..\src\main.c:71: DISPLAY_ON;																	// TURNS ON THE GAMEBOY LCD
	ldh	a, (_LCDC_REG+0)
	or	a, #0x80
	ldh	(_LCDC_REG+0),a
;..\src\main.c:72: NR52_REG = 0x8F;															// TURN SOUND ON
	ld	a, #0x8f
	ldh	(_NR52_REG+0),a
;..\src\main.c:73: NR51_REG = 0x11;															// ENABLE SOUND CHANNELS
	ld	a, #0x11
	ldh	(_NR51_REG+0),a
;..\src\main.c:74: NR50_REG = 0x1F;															// VOLUME MAX = 0x77, MIN = 0x00	
	ld	a, #0x1f
	ldh	(_NR50_REG+0),a
;..\src\main.c:76: initrand(DIV_REG);															// SEED OUR RANDOMIZER
	ldh	a, (_DIV_REG+0)
	ld	c, a
	ld	b, #0x00
	push	bc
	call	_initrand
	add	sp, #2
;..\src\main.c:78: set_sprite_data(0, 14, sprites);											// STORE OUR SPRITE DATA AT THE START OF SPRITE VRAM
	ld	hl, #_sprites
	push	hl
	ld	a, #0x0e
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_set_sprite_data
	add	sp, #4
;..\src\main.c:79: set_bkg_data(0, 4, myBkgData);												// STORE OUR BKG DATA AT THE START OF BKG VRAM - NOTE, THE WINDOW LAYER SHARED THE BKG VRAM BY DEFAULT
	ld	hl, #_myBkgData
	push	hl
	ld	a, #0x04
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_set_bkg_data
	add	sp, #4
;..\src\main.c:81: playerX = 64;																// PLAYERS INITAL X POSITION
	ld	hl, #_playerX
	ld	(hl), #0x40
;..\src\main.c:82: playerY = 64;																// PLAYERS INITAL Y POSITION
	ld	hl, #_playerY
	ld	(hl), #0x40
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:999: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 0x0002)
	ld	(hl), #0x00
;..\src\main.c:86: for (i=0; i !=10; i++){													// OUR ENEMY POSITION LOOP - NOTE, USE !=, NOT < TO SCRAPE BACK SOME CPU TIME
	ld	hl, #_i
	ld	(hl), #0x00
00107$:
;..\src\main.c:88: eX[i] = 16+(rand() >> 1);												// RANDOM X POSITION 16 - 144
	ld	a, #<(_eX)
	ld	hl, #_i
	add	a, (hl)
	ld	c, a
	ld	a, #>(_eX)
	adc	a, #0x00
	ld	b, a
	push	bc
	call	_rand
	ld	a, e
	pop	bc
	sra	a
	add	a, #0x10
	ld	(bc), a
;..\src\main.c:89: eY[i] = 16+(rand() >> 1);												// RANDOM Y POSITION 16 - 144
	ld	a, #<(_eY)
	ld	hl, #_i
	add	a, (hl)
	ld	c, a
	ld	a, #>(_eY)
	adc	a, #0x00
	ld	b, a
	push	bc
	call	_rand
	ld	a, e
	pop	bc
	sra	a
	add	a, #0x10
	ld	(bc), a
;..\src\main.c:90: set_sprite_tile(i+1, 2);												// ENEMIES SRITE TILE - SET TO SPRITE 2
	ld	hl, #_i
	ld	e, (hl)
	inc	e
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:999: shadow_OAM[nb].tile=tile;
	ld	bc, #_shadow_OAM+0
	xor	a, a
	ld	l, e
	ld	h, a
	add	hl, hl
	add	hl, hl
	add	hl, bc
	inc	hl
	inc	hl
	ld	(hl), #0x02
;..\src\main.c:91: move_sprite(i+1,eX[i], eY[i]);											// POSITION ENEMIES	
	ld	a, #<(_eY)
	ld	hl, #_i
	add	a, (hl)
	ld	c, a
	ld	a, #>(_eY)
	adc	a, #0x00
	ld	b, a
	ld	a, (bc)
	ld	b, a
	ld	a, #<(_eX)
	add	a, (hl)
	ld	e, a
	ld	a, #>(_eX)
	adc	a, #0x00
	ld	d, a
	ld	a, (de)
	ld	c, a
	ld	e, (hl)
	inc	e
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:1072: OAM_item_t * itm = &shadow_OAM[nb];
	ld	d, #0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, hl
	ld	de, #_shadow_OAM
	add	hl, de
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:1073: itm->y=y, itm->x=x;
	ld	a, b
	ld	(hl+), a
	ld	(hl), c
;..\src\main.c:86: for (i=0; i !=10; i++){													// OUR ENEMY POSITION LOOP - NOTE, USE !=, NOT < TO SCRAPE BACK SOME CPU TIME
	ld	hl, #_i
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x0a
	jr	NZ, 00107$
;..\src\main.c:98: for (j=0; j != 18; j++){
	ld	hl, #_j
	ld	(hl), #0x00
00111$:
;..\src\main.c:100: for (i=0; i != 20; i++){		
	ld	hl, #_i
	ld	(hl), #0x00
00109$:
;..\src\main.c:101: randomBkgTiles[i] = rand() % 4;		
	ld	a, #<(_randomBkgTiles)
	ld	hl, #_i
	add	a, (hl)
	ld	c, a
	ld	a, #>(_randomBkgTiles)
	adc	a, #0x00
	ld	b, a
	push	bc
	call	_rand
	pop	bc
	ld	a, e
	rla
	sbc	a, a
	ld	d, a
	push	bc
	ld	hl, #0x0004
	push	hl
	push	de
	call	__modsint
	add	sp, #4
	pop	bc
	ld	a, e
	ld	(bc), a
;..\src\main.c:100: for (i=0; i != 20; i++){		
	ld	hl, #_i
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x14
	jr	NZ, 00109$
;..\src\main.c:104: set_bkg_tiles(0,j,20,1,randomBkgTiles);									// SET A LINE OF BKG DATA (X, Y, W, H, DATA)
	ld	hl, #_randomBkgTiles
	push	hl
	ld	de, #0x0114
	push	de
	ld	a, (#_j)
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_set_bkg_tiles
	add	sp, #6
;..\src\main.c:98: for (j=0; j != 18; j++){
	ld	hl, #_j
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x12
	jr	NZ, 00111$
;..\src\main.c:107: }
	ret
;..\src\main.c:112: void updatePlayer(){
;	---------------------------------
; Function updatePlayer
; ---------------------------------
_updatePlayer::
;..\src\main.c:117: if (joypad() & J_UP){
	call	_joypad
	bit	2, e
	jr	Z, 00104$
;..\src\main.c:118: playerY--;
	ld	hl, #_playerY
	dec	(hl)
;..\src\main.c:119: if (playerY == 15){
	ld	a, (hl)
	sub	a, #0x0f
	jr	NZ, 00104$
;..\src\main.c:120: playerY = 16;
	ld	hl, #_playerY
	ld	(hl), #0x10
00104$:
;..\src\main.c:125: if (joypad() & J_DOWN){
	call	_joypad
	bit	3, e
	jr	Z, 00108$
;..\src\main.c:126: playerY++;
	ld	hl, #_playerY
	inc	(hl)
;..\src\main.c:127: if (playerY == 153){
	ld	a, (hl)
	sub	a, #0x99
	jr	NZ, 00108$
;..\src\main.c:128: playerY = 152;
	ld	hl, #_playerY
	ld	(hl), #0x98
00108$:
;..\src\main.c:133: if (joypad() & J_LEFT){
	call	_joypad
	bit	1, e
	jr	Z, 00112$
;..\src\main.c:134: playerX--;
	ld	hl, #_playerX
	dec	(hl)
;..\src\main.c:135: if (playerX == 7){
	ld	a, (hl)
	sub	a, #0x07
	jr	NZ, 00112$
;..\src\main.c:136: playerX = 8;
	ld	hl, #_playerX
	ld	(hl), #0x08
00112$:
;..\src\main.c:141: if (joypad() & J_RIGHT){
	call	_joypad
	ld	a, e
	rrca
	jr	NC, 00116$
;..\src\main.c:142: playerX++;
	ld	hl, #_playerX
	inc	(hl)
;..\src\main.c:143: if (playerX == 161){
	ld	a, (hl)
	sub	a, #0xa1
	jr	NZ, 00116$
;..\src\main.c:144: playerX = 160;
	ld	hl, #_playerX
	ld	(hl), #0xa0
00116$:
;..\src\main.c:152: if (joypad() & J_A){
	call	_joypad
	bit	4, e
	jr	Z, 00118$
;..\src\main.c:154: NR11_REG = 0x7f; 													// SQUARE WAVE DUTY
	ld	a, #0x7f
	ldh	(_NR11_REG+0),a
;..\src\main.c:155: NR12_REG = 0x7f; 													// VOLUME 0 = quietest, 255 = loudest
	ld	a, #0x7f
	ldh	(_NR12_REG+0),a
;..\src\main.c:156: NR13_REG = DIV_REG;													// LOWER BITS OF SOUND FREQ
	ldh	a, (_DIV_REG+0)
	ldh	(_NR13_REG+0),a
;..\src\main.c:157: NR14_REG = 0x80 + (DIV_REG % 8); 									// LARGER SOUND FREQ - MINIMUM OF 128 - TOP 3 BYTES - ANY LESS = SOUND CHANNEL SWITCHES OFF
	ldh	a, (_DIV_REG+0)
	and	a, #0x07
	add	a, #0x80
	ldh	(_NR14_REG+0),a
	jr	00119$
00118$:
;..\src\main.c:159: NR11_REG = 0x00;													// NO A BUTTON - NO SOUND
	ld	a, #0x00
	ldh	(_NR11_REG+0),a
;..\src\main.c:160: NR12_REG = 0x00;
	ld	a, #0x00
	ldh	(_NR12_REG+0),a
;..\src\main.c:161: NR13_REG = 0x00;
	ld	a, #0x00
	ldh	(_NR13_REG+0),a
;..\src\main.c:162: NR14_REG = 0x00;
	ld	a, #0x00
	ldh	(_NR14_REG+0),a
00119$:
;..\src\main.c:167: move_sprite(0,playerX,playerY);												// POSITION OUR SPRITE ON THE SCREEN	
	ld	hl, #_playerY
	ld	b, (hl)
	ld	hl, #_playerX
	ld	c, (hl)
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:1072: OAM_item_t * itm = &shadow_OAM[nb];
	ld	hl, #_shadow_OAM
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:1073: itm->y=y, itm->x=x;
	ld	a, b
	ld	(hl+), a
	ld	(hl), c
;..\src\main.c:169: j=0;																		// RE-USE J AS A FLAG TO SEE IF WE HAVE COLLIDED WITH AN ENEMY
	ld	hl, #_j
	ld	(hl), #0x00
;..\src\main.c:171: for (i=0; i != 10; i++){												// LOOP THROUGH OUR 10 ENEMIES
	ld	hl, #_i
	ld	(hl), #0x00
00129$:
;..\src\main.c:173: if (collisionCheck(playerX, playerY, 8, 8, eX[i], eY[i], 8, 8) == 1){
	ld	a, #<(_eY)
	ld	hl, #_i
	add	a, (hl)
	ld	c, a
	ld	a, #>(_eY)
	adc	a, #0x00
	ld	b, a
	ld	a, (bc)
	ld	b, a
	ld	a, #<(_eX)
	add	a, (hl)
	ld	e, a
	ld	a, #>(_eX)
	adc	a, #0x00
	ld	d, a
	ld	a, (de)
	ld	h, #0x08
	push	hl
	inc	sp
	ld	h, #0x08
	ld	l, b
	push	hl
	ld	d,a
	ld	e,#0x08
	push	de
	ld	a, #0x08
	push	af
	inc	sp
	ld	a, (#_playerY)
	push	af
	inc	sp
	ld	a, (#_playerX)
	push	af
	inc	sp
	call	_collisionCheck
	add	sp, #8
	dec	e
	jr	NZ, 00130$
;..\src\main.c:174: j= 1;																// IF WE COLLIDED, SET OUR FLAG VARIABLE, J TO 1
	ld	hl, #_j
	ld	(hl), #0x01
00130$:
;..\src\main.c:171: for (i=0; i != 10; i++){												// LOOP THROUGH OUR 10 ENEMIES
	ld	hl, #_i
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x0a
	jr	NZ, 00129$
;..\src\main.c:180: switch (j){
	ld	a, (#_j)
	or	a, a
	jr	NZ, 00124$
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:999: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 0x0002)
	ld	(hl), #0x00
;..\src\main.c:184: break;
	ret
;..\src\main.c:187: default:
00124$:
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:999: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 0x0002)
	ld	(hl), #0x01
;..\src\main.c:190: }
;..\src\main.c:192: }
	ret
;..\src\main.c:198: UINT8 collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2){
;	---------------------------------
; Function collisionCheck
; ---------------------------------
_collisionCheck::
	add	sp, #-4
;..\src\main.c:200: if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)){
	ldhl	sp,	#10
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	ldhl	sp,	#12
	ld	c, (hl)
	ld	b, #0x00
	pop	hl
	push	hl
	add	hl, bc
	push	hl
	ld	a, l
	ldhl	sp,	#4
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#3
	ld	(hl), a
	ldhl	sp,	#6
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#2
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	ld	a, b
	ld	d, a
	bit	7, (hl)
	jr	Z, 00129$
	bit	7, d
	jr	NZ, 00130$
	cp	a, a
	jr	00130$
00129$:
	bit	7, d
	jr	Z, 00130$
	scf
00130$:
	jp	NC, 00102$
	ldhl	sp,	#8
	ld	e, (hl)
	ld	d, #0x00
	ld	a, e
	add	a, c
	ld	c, a
	ld	a, d
	adc	a, b
	ld	b, a
	ldhl	sp,	#0
	ld	a, (hl)
	sub	a, c
	inc	hl
	ld	a, (hl)
	sbc	a, b
	ld	d, (hl)
	ld	a, b
	bit	7,a
	jr	Z, 00131$
	bit	7, d
	jr	NZ, 00132$
	cp	a, a
	jr	00132$
00131$:
	bit	7, d
	jr	Z, 00132$
	scf
00132$:
	jr	NC, 00102$
	ldhl	sp,	#13
	ld	c, (hl)
	ld	b, #0x00
	dec	hl
	dec	hl
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	pop	hl
	push	hl
	add	hl, bc
	push	hl
	ld	a, l
	ldhl	sp,	#4
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#3
	ld	(hl), a
	ldhl	sp,	#7
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#2
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	ld	a, b
	ld	d, a
	bit	7, (hl)
	jr	Z, 00133$
	bit	7, d
	jr	NZ, 00134$
	cp	a, a
	jr	00134$
00133$:
	bit	7, d
	jr	Z, 00134$
	scf
00134$:
	jr	NC, 00102$
	ldhl	sp,	#9
	ld	e, (hl)
	ld	d, #0x00
	ld	a, e
	add	a, c
	ld	c, a
	ld	a, d
	adc	a, b
	ld	b, a
	ldhl	sp,	#0
	ld	a, (hl)
	sub	a, c
	inc	hl
	ld	a, (hl)
	sbc	a, b
	ld	d, (hl)
	ld	a, b
	bit	7,a
	jr	Z, 00135$
	bit	7, d
	jr	NZ, 00136$
	cp	a, a
	jr	00136$
00135$:
	bit	7, d
	jr	Z, 00136$
	scf
00136$:
	jr	NC, 00102$
;..\src\main.c:201: return 1;
	ld	e, #0x01
	jr	00107$
00102$:
;..\src\main.c:203: return 0;
	ld	e, #0x00
00107$:
;..\src\main.c:206: }
	add	sp, #4
	ret
	.area _CODE
	.area _CABS (ABS)
