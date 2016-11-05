// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Do multiplication of R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

	@R0
	D=M
	@x
	M=D // x = R0
	
	@R1
	D=M
	@y
	M=D // y = R1
	
	@R2
	M=0 // R2 = 0
	
	@15
	D=M
	@counter
	M=D // counter = 15
	
	@result
	M=0
	
(WHILE)
	
	@counter
	D=M
	@temp1
	M=1<D
	
	@temp1
	D=M
	@y
	D=D&M
	@STOP_POINT
	D;JLE

	@x
	D=M
	@counter
	D=D<M
	@result
	M=M+D

(STOP_POINT)
	@counter
	M=M-1
	
	@counter
	D=M
	@WHILE
	D;JGE
	
	@result
	D=M
	@R2
	M=D
	
(END)
	
	@END
	0;JMP