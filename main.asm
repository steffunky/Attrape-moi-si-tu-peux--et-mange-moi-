; SNES Initialization Tutorial code
; This code is in the public domain.

.include "Header.inc"
.include "Snes_Init.asm"

	;; 1:source 2:destination 3 : size
.macro LoadPalette
    lda #\2
    sta $2121       ; Start at START color
    lda #:\1        ; Using : before the parameter gets its bank.
    ldx #\1         ; Not using : gets the offset address.
    ldy #(\3 * 2)   ; 2 bytes for every color

	phb
    php         ; Preserve Registers

    stx $4302   ; Store data offset into DMA source offset
    sta $4304   ; Store data bank into DMA source bank
    sty $4305   ; Store size of data block
    stz $4300   ; Set DMA Mode (byte, normal increment)
    lda #$22    ; Set destination register ($2122 - CGRAM Write)
    sta $4301
    lda #$01    ; Initiate DMA transfer
    sta $420B

    plp
    plb
.endm

	;; 1: source 2: destination 3:size
.MACRO LoadBlockToVRAM
    lda #$80
    sta $2115       ; Set VRAM transfer mode to word-access, increment by 1

    ldx #\2         ; DEST
    stx $2116       ; $2116: Word address for accessing VRAM.
    lda #:\1        ; SRCBANK
    ldx #\1         ; SRCOFFSET
    ldy #\3         ; SIZE

    phb
    php         ; Preserve Registers

    stx $4302   ; Store Data offset into DMA source offset
    sta $4304   ; Store data Bank into DMA source bank
    sty $4305   ; Store size of data block

    lda #$01
    sta $4300   ; Set DMA mode (word, normal increment)
    lda #$18    ; Set the destination register (VRAM write register)
    sta $4301
    lda #$01    ; Initiate DMA transfer (channel 1)
    sta $420B

    plp         ; restore registers
    plb
.ENDM

	
; Needed to satisfy interrupt definition in "Header.inc".
 VBlank:
   RTI ; 

.bank 0
.section "MainCode"
	 
Start:
    Snes_Init
	

Main:	
	rep		#$10		; registres X/Y en 16 bits
	sep     #$20        ; Set the A register to 8-bit.
	LoadPalette UntitledPalette, 0, 256
	LoadBlockToVRAM UntitledData, 0, 2048
    lda #%1000000
    sta $2105
Game:
	ldx #$0400 			;BG1 Tilemap Offset
    stx $2116

    lda #$06
    sta $2118
	jsr SetupVideo
	
Forever:
	jmp Forever
	
SetupVideo:
    php

    lda #%00010011
    sta $2105           ; Set Video mode 0, 8x8 tiles, 4 color BG1/BG2/BG3/BG4

    lda #$04			; Set BG1's Tile Map offset to $0400 (Word address)in
    sta $2107           ; And the Tile Map size to 32x32

    stz $210B           ; Set BG1's Character VRAM offset to $0000 (word address)

    lda #$01            ; Enable BG1
    sta $212C

    lda #$0F
    sta $2100           ; Turn on screen, full Brightness
    plp
    rts
	 
.ends


	;; Registre NMI 0x4210 flag sur bit 7

	;; WAI, attend une interruption, VBLANK en general

	;; Registre 0x2122 gere la couleur de transparence, il faut charger
	;; les 8bit de poids faible puis les 8 autres
	;; la couleur est sur 16 bit BGR, le bit de poids fort est a 0
	;; exemple rouge=0|00000|00000|11111

	
.bank 1 slot 0
.org 0
.section "Flap"
.include "flappy4.inc"
.ends

