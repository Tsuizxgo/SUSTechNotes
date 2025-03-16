.include "macro_print_str.asm"
 .data
 str:
 .text
 # int i,j
 main:
 li t1,1
 j loop2

 loop2:
 li s0,9
 bgt t1,s0,exit
 li t0,1
 j loop1
 endloop1:
 addi t1,t1,1
 print_string("\n")
 j loop2
 
 loop1:
 bgt t0,t1,endloop1
 mv a0,t0
 li a7,1
 ecall
 
 print_string(" * ")
 mv a0,t1
 li a7,1
 ecall
 
 print_string(" = ")
 mul a0,t0,t1
 li a7, 1
 ecall
 
 print_string(" ")
 addi t0,t0,1
 j loop1
 
 exit:
 end