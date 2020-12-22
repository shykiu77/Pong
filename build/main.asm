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
	.globl _sprite
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_sprite::
	.ds 16
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
;..\src\/sprite.c:19: unsigned char sprite[] =
	ld	hl, #_sprite
	ld	(hl), #0x7e
	ld	hl, #(_sprite + 0x0001)
	ld	(hl), #0x7e
	ld	hl, #(_sprite + 0x0002)
	ld	(hl), #0x99
	ld	hl, #(_sprite + 0x0003)
	ld	(hl), #0x99
	ld	hl, #(_sprite + 0x0004)
	ld	(hl), #0x81
	ld	hl, #(_sprite + 0x0005)
	ld	(hl), #0x81
	ld	hl, #(_sprite + 0x0006)
	ld	(hl), #0xa5
	ld	hl, #(_sprite + 0x0007)
	ld	(hl), #0xa5
	ld	hl, #(_sprite + 0x0008)
	ld	(hl), #0x81
	ld	hl, #(_sprite + 0x0009)
	ld	(hl), #0x81
	ld	hl, #(_sprite + 0x000a)
	ld	(hl), #0xdb
	ld	hl, #(_sprite + 0x000b)
	ld	(hl), #0xdb
	ld	hl, #(_sprite + 0x000c)
	ld	(hl), #0xc3
	ld	hl, #(_sprite + 0x000d)
	ld	(hl), #0xc3
	ld	hl, #(_sprite + 0x000e)
	ld	(hl), #0x3c
	ld	hl, #(_sprite + 0x000f)
	ld	(hl), #0x3c
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;..\src\main.c:4: void main() {
;	---------------------------------
; Function main
; ---------------------------------
_main::
;..\src\main.c:5: SPRITES_8x8;
	ldh	a, (_LCDC_REG+0)
	and	a, #0xfb
	ldh	(_LCDC_REG+0),a
;..\src\main.c:6: set_sprite_data(0, 8, sprite);
	ld	hl, #_sprite
	push	hl
	ld	a, #0x08
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_set_sprite_data
	add	sp, #4
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:999: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 0x0002)
	ld	(hl), #0x00
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:1072: OAM_item_t * itm = &shadow_OAM[nb];
	ld	hl, #_shadow_OAM
;C:/Users/carlo/Desktop/Periodo 7/IHS/Projeto Snake-Corona/tools/gbdk/include/gb/gb.h:1073: itm->y=y, itm->x=x;
	ld	a, #0x32
	ld	(hl+), a
	ld	(hl), #0x32
;..\src\main.c:9: SHOW_SPRITES;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x02
	ldh	(_LCDC_REG+0),a
;..\src\main.c:10: }
	ret
	.area _CODE
	.area _CABS (ABS)
