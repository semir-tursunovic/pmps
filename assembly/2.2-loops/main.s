	.syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.syntax unified
	.thumb

.global main

.section .text.main

main:

/*
	y = 0;
	for (x = 10; x > 0; x--)
	{
		y = y + x;
	}
*/
	mov r2,#0
	mov r3,#10
for:
	cmp r3,#0
	ble endfor
	add r2,r2,r3
	sub r3,#1
	b for
endfor:
	mov r2,#0
	mov r3,#10

/*
x = 10
while(x > 0)
{
	x = x - 1
}
*/
while:
	cmp r3,#0
	ble endwhile
	sub r3,#1
	b while
endwhile:
	mov r2,#0
	mov r3,#10
/*
	x = 10;
	do
	{
		x = x - 1
	}while(x > 0);
*/
dowhile:
	sub r3,#1
	cmp r3,#0
	bgt dowhile
enddowhile:
	b loop



loop:
	nop
	nop
	nop
	b loop
