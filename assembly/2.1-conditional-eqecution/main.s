	.syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.syntax unified
	.thumb

.global main

.section .text.main

main:
	ITTE   NE            /*Next 3 instructions are conditional */
	andne  R0, R0, R1    /*ANDNE does not update condition flags*/
	addsne R2, R2, #1    /*ADDSNE updates condition flags*/
	moveq  R2, R3        /*Conditional move*/

	ITE    GT            /*Next 2 instructions are conditional*/
	addgt  R1, R0, #55   /*Conditional addition in case the GT is true*/
	addle  R1, R0, #48   /*Conditional addition in case the GT is not true*/

	ITTEE  EQ            /*Next 4 instructions are conditional*/
	moveq  R0, R1        /*Conditional MOV*/
	addeq  R2, R2, #10   /*Conditional ADD*/
	andne  R3, R3, #1    /*Conditional AND*/
	bne  loop			 /*Branch instruction can only be used in the last instruction of an IT block*/
	b loop

loop:
	nop
	nop
	nop
	b loop
