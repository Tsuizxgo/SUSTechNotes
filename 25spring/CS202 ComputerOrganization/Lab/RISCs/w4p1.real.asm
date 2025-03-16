.include "macro_print_str.asm"

.text
main:
	li a7, 5
	ecall
	
	jal feibo
	
	mv a1, a0
	li a7, 1
	ecall
	li a7,10
	ecall


feibo:
	#ruzhan
	addi sp , sp, -12
	sw ra, 0(sp)
	sw a0, 4(sp)
	
	li t0, 2
	blt a0, t0, ifLessThan2
	
	addi a0, a0, -1
	jal feibo
	sw a0, 8(sp)
	
	lw a0, 4(sp)
	addi a0, a0, -2
	jal feibo
	
	lw t1, 8(sp)
	add a0, a0, t1
	
	j end

ifLessThan2:
	li a0, 1

end:
	lw ra,0(sp)
	addi sp, sp,12
	ret