// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

  @24576 // last screen address
  D=A
  @screenlast
  M=D

(FILLSCREEN)
  @SCREEN
  D=A
  @screencurrent
  M=D

(LOOP)
  // for loop
  @screencurrent
  D=M
  @screenlast
  D=D-M
  @FILLSCREEN
  D;JEQ

  // check key pressed 
  @KBD
  D=M
  @WHITE
  D;JEQ

(BLACK)
  @screencurrent
  A=M
  M=-1

  @ENDIF
  0;JMP
(WHITE)
  @screencurrent
  A=M
  M=0
(ENDIF)

  // set next pixel address
  @screencurrent
  M=M+1

  @LOOP
  0;JMP
