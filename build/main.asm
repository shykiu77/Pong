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
	.globl _printf
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
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
;..\src\main.c:15: void main() {
;	---------------------------------
; Function main
; ---------------------------------
_main::
;..\src\main.c:19: printf("Hello World!");
	ld	hl, #___str_0
	push	hl
	call	_printf
	add	sp, #2
;..\src\main.c:22: printf("\n\nPress Start");
	ld	hl, #___str_1
	push	hl
	call	_printf
	add	sp, #2
;..\src\main.c:23: }
	ret
___str_0:
	.ascii "Hello World!"
	.db 0x00
___str_1:
	.db 0x0a
	.db 0x0a
	.ascii "Press Start"
	.db 0x00
	.area _CODE
	.area _CABS (ABS)
