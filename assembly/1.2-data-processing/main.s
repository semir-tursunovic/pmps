	.syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.thumb

.global main

.section .text.main
main:
	bl o_mov
	bl o_add
	bl o_sub
	bl o_rsb
	bl o_bitwise

	b loop

o_mov:
	mov r0,#0x00ff
	mov r1,#65
	mov r2,r1
	/*mov r3,#12340000*/
	mov r3,r0,LSL #16
	mvn r1,r0
	bx  r14

o_add:
	mov r0,0xff
	mvn r1,r0
	mov r3,#0
	add r2,r2,r1
	adds r2,r1
	adc r2,r3
	bx r14

o_sub:
	mov r0,#20
	mvn r1,#16
	mov r3,#0
	mov r2,r0
	sub r2,r2,r1
	subs r2,r1
	sbc r2,r1
	bx r14

o_rsb:
	mov r0,#20
	mov r1,#16
	mov r3,#0
	mov r2,r0
	rsb r2,r2,r1
	rsb r2,r1
	bx r14
o_bitwise:
	mov r0,#0x00ff
	mov r1,#0xfff0
	and r3,r0,r1
	orr r3,r0,r1
	eor r3,r0,r1
	bic r3,r0,r1
	bx r14

o_cmp:
	mov r0,#0x0f
	mov r1,#0xf0
	mov r2,#0x0f
	cmp r0,r1
	cmp r0,r2
	cmn	r0,r1
	cmn r0,r2
	teq	r0,r1
	teq r0,r2
	tst	r0,r1
	tst r0,r2
loop:
	nop
	nop
	nop
	b loop
