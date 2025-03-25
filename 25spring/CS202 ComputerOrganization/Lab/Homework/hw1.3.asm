.data
arr:        .space 200
.text
main:	li a7,5
	ecall
	mv s0,a0
	
	li t0,0
	la t1,arr
	
loop:	bge t0,s0,sort_start
	li a7,5
	ecall
	sw a0,0(t1)
	
	addi t1, t1,4
	addi t0,t0,1
	j loop
sort_start:
	addi t0,s0,-1
outer_loop:
	blt t0,zero,print
	
	li t1,0
	la t2,arr
inner_loop:
	bge t1,t0,out_next
	
	lw t3, 0(t2)
	lw t4, 4(t2)
	
	ble t3,t4, no_swap
	
	sw t3,4(t2)
	sw t4,0(t2)
	
	j inner_loop

no_swap:
	addi t2,t2,4
	addi t1,t1,1
	j inner_loop
	
out_next:
	addi t0,t0,-1
	j outer_loop
print:
li t0, 0
    la t1, arr         

print_loop:
    bge t0, s0, exit  
    lw a0, 0(t1)        
    li a7, 1           
    ecall

    li a7, 11          
    li a0, 10         
    ecall

    addi t1, t1, 4     
    addi t0, t0, 1     
    j print_loop        

exit:
    li a7, 10          
    ecall