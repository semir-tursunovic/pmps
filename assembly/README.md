# Introduction
In this part of the course we will take a look at the ARM assembly intruction set and internal arhitecture of the ARM CPU.

# ARM-32 Registers
For the purposes of the normal programmer in "User Mode" the ARM has 15 registers. R0-R12 are free for us to do whatever we want, R13 is the Stack Pointer (also addressable as SP), R15 is the Program Counter (PC)

R14 may be surprising to those familiar with other CPUs, when we call a subroutine (With BL - Branch and Link) the return address is not pushed onto the stack, instead it's moved into R14/LR... to return from the subroutine we need to move the R14/LR register into R15/PC.

This poses a problem, as nesting subroutines will lose the return value, if this is needed, the best solution is to simply push R14/LR onto the stack at the start of a sub, and pop PC/R15 off the stack at the end.

|	| 	32 Bit registers	|	Use case		|
|---	|	---				|	---			|
|R0	|	R0				|				|
|R1	|	R1				|				|
|R2	|	R2				|				|
|R3	|	R3				|				|
|R4	|	R4				|				|
|R5	|	R5				|				|
|R6	|	R6				|				|
|R7	|	R7				|				|
|R8	|	R8				|				|
|R9	|	R9				|				|
|R10 |	R10				|				|
|R11 |	R11/FP			|Frame Pointer (Optional)				|
|R12 |	R12/IP			|Intra Procedure Call (Optional)		|
|R13 |	SP				|Stack Pointer				|
|R14 |	LR/LK			|Link register		|
|R15 |	PC				|System program counter				|

The Application Program Status Register (APSR) holds copies of the Arithmetic Logic Unit (ALU) status flags. They are also known as the condition code flags. They are used to determine whether conditional instructions are executed or not.

![xPSR Register](images/arm-xpsr-register.png  "xPSR Register")

where
<ul>
<li> <b>N</b> - Negative condition flag. Set to bit[31] of the result of the instruction. If the result is
regarded as a two's complement signed integer, then the processor sets N to 1 if the result
is negative, and sets N to 0 if it is positive or zero. </li>
<li> <b>Z</b> - Zero condition flag. Set to 1 if the result of the instruction is zero, and to 0 otherwise. A
result of zero often indicates an equal result from a comparison. </li>
<li> <b>C</b> - Carry condition flag. Set to 1 if the instruction results in a carry condition, for example an
unsigned overflow on an addition. </li>
<li> <b>V</b> - Overflow condition flag. Set to 1 if the instruction results in an overflow condition, for
example a signed overflow on an addition.</li>
<li> <b>Q</b> - Set to 1 to indicate overflow or saturation occurred in some instructions, normally related
to digital signal processing (DSP </li>
<li> <b>GE</b> - The Greater than or Equal flags</li>
</ul>

# ARM Instruction set

## Syntax
General syntax of the ARM instruction is:
```
<op><cc><S> 	Rd, <operands>
```
where:

<ul>
<li> <b>op</b> is ARM instruction </li>
<li> <b>cc</b> is compare flag </li>
<li> <b>S</b>  </li>
<li> <b>Rd</b> destination register </li>
<li> <b>operands</b> arguments for the instruction </li>
</ul>

Following images describes format of the ARM instruction.
![ARM-Instruction-Format](./images/arm-instruction-format.png  "ARM Instruction format")

## Data processing
### MOV
MOV instruction is used for loading the immediate value to register and for copying value from one register to another. Basic sytanx of the MOV instruction is:
```
mov destination,source
```

<b> Loading the immediate value</b>
```
mov  r0,#0x1234			; load value 0x1234 to register r0
mov  r1,#56				; load value 56 to register r1
mov  r2,#0x12340000		; this will generate compiler error because we can only load 2 bytes using the MOV instruction
```
<b> Coppying value from one register to another </b>
```
mov r0,pc				; this will coppy value from the PC  to register r0
```
/ref the above image. As we saw before, we can't load to register immediate value greater than 2 bytes.   At least, we can't achive this with only one instruction. But there is workaround. We can use left shift  to get desired value stored in the register. But this value that will be shifted must be stored in the internal register first.


<b> Loading the immediate value larger then 2 bytes</b>
```
mov  r0,#0x1234			; load value 0x1234 to register r0
mov  r1,r0,LSL 4			; load value 56 to register r1
```
### MVN
This instruction works just like the **MOV** instruction, but instead of loading the provided value to the destination register, this instruction will load first complement of the specified value. For example, instruction
```
mvn r0,#0x00FF
```
will load value *#0xff00* to the register *r0.*
### ADD
Basic sytanx of the ADD instruction is:
```
add 		r0,r1		; r0 = r0 + r1
add 		r0,r0,r1 	; r0= r0 + r1
adc 		r0,r1		; r0 = r0 + r1 + C
```
This instruction will add values from two registers and move them to destination register. We have special case when one of the operands is also the destination register. In this case we can only specify destination register and we don't need to specify second operand because this operans is value from the destination register.

Addin sufix c to this command will take in consideration the value of the carry flag.

### SUB
Basic sytanx of the SUB instruction is:
```
sub 		r0,r1		; r0 = r0 - r1
sub			r0,r0,r1 	; r0= r0 - r1
sbc 		r0,r1		; r0 = r0 - r1 - !C
```
This instruction will add values from two registers and move them to destination register. We have special case when one of the operands is also the destination register. In this case we can only specify destination register and we don't need to specify second operand because this operans is value from the destination register.

Addin sufix c to this command will take in consideration the value of the carry flag.

### RSB
This instruction works just like the SUB instruction. Only differenc is that the position of operans are swapped.
Basic sytanx of the RSB instruction is:
```
rsb 		r0,r1		; r0 = r1 - r0
rsb			r0,r0,r1 		; r0= r1 - r0
```

### Bitwise operation
Following bitwise operations are supported.
```
and 				r0,r1,r2		;r0 = r1 & r2
orr				r0,r1,r2		;r0 = r1 | r2
eor				r0,r1,r2		;r0 = r1 ^ r2
bic 				r0,r1,r2		;r0 = r1 & (~r2)
```
### Comparison operations
Basic sytanx for comparison instruction is
```
<op><cc> Rn,Operand2
```
We can use following operations:
<ul>
<li><b>CMP</b> - Compare (Flags set to result of (Rn − Operand2))</li>
<li><b>CMN</b> - Compare negative (Flags set to result of (Rn + Operand2))</li>
<li><b>TST</b> - bitwise test (Flags set to result of (Rn AND Operand2).)</li>
<li><b>TEQ</b> -  test equivalence (Flags set to result of (Rn EOR Operand2))</li>
</ul>
Comparisons produce no results – they just set condition codes. Ordinary instructions will also set condition codes if the “S” bit is set. The “S” bit is implied for comparison instructions.

These instructions update the N, Z, C. For example, the CMP instruction will set the confition codes as follows:
<ul>
        <li> N =1 if the most significant bit of (r1 - r2) is 1, i.e. r2 > r1 </li>
        <li> Z = 1 if (r1 - r2) = 0, i.e. r1 = r2 </li>
        <li> C = 1 if r1 and r2 are both unsigned integers AND (r1 < r2) </li>
        <li> V = 1 if r1 and r2 are both signed integers AND (r1 < r2)</li>
</ul>

Instructions **TST** and **TEQ** will not affect C flag and this flag will keep previous value.
## Conditional eqecution
The following table lists the available condition codes, their meanings, and the status of the flags that are tested.

| 	Condition Code 	| Meaning (for cmp or subs) 	|	Status of Flags|
|---					|---						|---|
|EQ 					|	Equal 				|Z=1|
|NE 					|Not Equal 				|Z=0|
|GT 					|Signed Greater Than 		|(Z=0) && (N=V)|
|LT 					|Signed Less Than 			|N!=V|
|GE 					|Signed Greater Than or Equal |N=V|
|LE 					|Signed Less Than or Equal 	|(Z=1) \|\| (N!=V)|
|CS or HS 			|Unsigned Higher or Same (or Carry Set)| 	C=1|
|CC or LO 			|Unsigned Lower (or Carry Clear) |	C=0|
|MI 					|Negative (or Minus) 		|N=1|
|PL 					|Positive (or Plus) 			|N=0|
|AL 	 				|Always executed 	 		|-|
|NV 	 				|Never executed 	 		|-|
|VS 	 				|Signed Overflow 	 		|V=1|
|VC 	 				|No signed Overflow 	 	|V=0|
|HI 	 				|Unsigned Higher 			|(C=1) && (Z=0)|
|LS 	 				|Unsigned Lower or same 	|(C=0) \|\| (Z=0)|

Syntax: IT{x{y{z}}} cond

- cond specifies the condition for the first instruction in the IT block
- x specifies the condition switch for the second instruction in the IT block
- y specifies the condition switch for the third instruction in the IT block
- z specifies the condition switch for the fourth instruction in the IT block

The structure of the IT instruction is “IF-Then-(Else)” and the syntax is a construct of the two letters T and E:

- IT refers to If-Then (next instruction is conditional)
- ITT refers to If-Then-Then (next 2 instructions are conditional)
- ITE refers to If-Then-Else (next 2 instructions are conditional)
- ITTE refers to If-Then-Then-Else (next 3 instructions are conditional)
- ITTEE refers to If-Then-Then-Else-Else (next 4 instructions are conditional)

Each instruction inside the IT block must specify a condition suffix that is either the same or logical inverse. This means that if you use ITE, the first and second instruction (If-Then) must have the same condition suffix and the third (Else) must have the logical inverse of the first two. Here are some examples from the ARM reference manual which illustrates this logic:

```
ITTE   NE           ; Next 3 instructions are conditional
ANDNE  R0, R0, R1   ; ANDNE does not update condition flags
ADDSNE R2, R2, #1   ; ADDSNE updates condition flags
MOVEQ  R2, R3       ; Conditional move

ITE    GT           ; Next 2 instructions are conditional
ADDGT  R1, R0, #55  ; Conditional addition in case the GT is true
ADDLE  R1, R0, #48  ; Conditional addition in case the GT is not true

ITTEE  EQ           ; Next 4 instructions are conditional
MOVEQ  R0, R1       ; Conditional MOV
ADDEQ  R2, R2, #10  ; Conditional ADD
ANDNE  R3, R3, #1   ; Conditional AND
BNE.W  dloop        ; Branch instruction can only be used in the last instruction of an IT block
```

Wrong syntax:

```
IT     NE           ; Next instruction is conditional     
ADD    R0, R0, R1   ; Syntax error: no condition code used in IT block.
```

Here are the conditional codes and theire opposite:
<table>
<thead><tr><th title="Field #1" colspan="2">Condition Code</th>
<th title="Field #2" colspan="2">Opposite</th>
</tr></thead>
<tbody><tr>
<td>Code </td>
<td>	Meaning</td>
<td> 	Code </td>
<td>	Meaning</td>
</tr>
<tr>
<td>EQ 	</td>
<td>Equal </td>
<td>	NE </td>
<td>	 Not Equal</td>
</tr>
<tr>
<td>HS(or CS) </td>
<td>	Unsigned higher or same(or carry set) </td>
<td>	LO(or CC) </td>
<td>	 Unsigned lower (or carry clear)</td>
</tr>
<tr>
<td>MI </td>
<td>	Negative </td>
<td>	PL 	</td>
<td> Positive or Zero</td>
</tr>
<tr>
<td>VS </td>
<td>	Signed Overflow</td>
<td> 	VC 	 </td>
<td>No Signed Overflow</td>
</tr>
<tr>
<td>HI </td>
<td>	Unsigned Higher </td>
<td>	LS 	</td>
<td> Unsigned Lower or Same</td>
</tr>
<tr>
<td>GE </td>
<td>	Signed Greater Than or Equal </td>
<td>	LT 	</td>
<td> Signed Less Than</td>
</tr>
<tr>
<td>GT </td>
<td>	 Signed Greater Than</td>
<td> 	LE </td>
<td>	 Signed Less Than or Equal</td>
</tr>
<tr>
<td>AL(or omitted)</td>
<td> 	 Always Executed </td>
<td colspan="2">	There is no opposite to AL</td>
</tr>
</tbody></table>
## Flow control
For the flow control we can use following instructions:
```
b <cond> 	label	; jump to the label subroutine
bl <cond> 	label	; coppy address of the next instruction to the LR and jump to the label subroutine
bx<cond>	label	; coppy content of the LR to PC (this is euqal to return from subroutine)
```

#Reference

1. [Peter Cockerell Book](http://www.peter-cockerell.net/aalp/html/frames.html)  
2. [Azeria Labs](https://azeria-labs.com/writing-arm-assembly-part-1/)
