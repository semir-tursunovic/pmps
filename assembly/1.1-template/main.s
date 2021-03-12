
.global main

.section .text.main

;;
;Main function will call different subroutines. This subroutines will demonstrate basic operations and instructions of the ARM CPU
;;
main:
	bl o_mov
	b loop

;;
;Operation mov
;;
o_mov:
	mov
	bx
loop:
	nop
	nop
	nop
	b loop
