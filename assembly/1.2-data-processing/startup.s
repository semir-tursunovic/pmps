	.syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.thumb

.global  g_pfnVectors


#Initializing the Bare minimum vector table
  	.section  .isr_vector,"a",%progbits
  	.type  g_pfnVectors, %object
  	.size  g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  	.word  _estack
  	.word  Reset_Handler

 	.section .text.Reset_Handler
	.weak Reset_Handler
 	.type Reset_Handler, %function

Reset_Handler:
 	bl main

