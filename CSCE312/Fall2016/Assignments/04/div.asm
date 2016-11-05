// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Div.asm

// Divides R0 by R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
	@R0
	D=M
	@x
	M=D	// x = R0

	@R1
	D=M
	@y
	M=D	// y = R1
	
	@0
	D=A
	@R2
	M=D	// R2 = 0
	
(WHILE)
	
	@x
	D=M	
	@END
	D;JLE	    

	@1
	D=A
	@R2
	M=M+D
	
	@y
	D=M
	@x
	M=M-D
	
	@WHILE
	0;JMP	
(END)	
	@END
	0;JMP	