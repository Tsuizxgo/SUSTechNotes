.text
main:
	li a7,5
	ecall
	mv a1,a0
	li a7,5
	ecall
	
	li t0,0
	li t1,1
	jal a
m:	## a0 ==2 a1==20
	mv a1,t1
	li t0,1
	li t1,1
	jal b
	
	#calculate a1/a0
c:	mv a0,t1

	li t0,0
	li t1,0
	jal s

g:	mv a0,t1
	li a7,1
	ecall
	li a7,10
	ecall

s:	ble a1,t0,g
	sub a1,a1,a0
	addi t1,t1,1
	jal s
	
a:
	bge t0,a0,m
	mul t1,t1,a1
	addi a1,a1,-1
	addi t0,t0,1
	jal a
	
b:	
	blt a0,t0,c
	mul t1,t1,a0
	addi a0,a0,-1
	jal b