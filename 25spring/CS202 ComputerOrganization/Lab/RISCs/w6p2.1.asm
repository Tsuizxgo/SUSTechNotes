.data
m1:.half -8 # multiplicand
m2:.half 9 # multiplier

.text
main:
	lh t0,m1
	lh t1,m2
	add t2, zero, zero

	mv s3,t1
	bge s3,zero,noNeg
	neg t1,t1 #t1<0 qvfan

noNeg:
	li a0,0
	li a1,16
loop:
	andi s2, t1, 1
	beq s2, zero, jumpAdd ## s2 zuidiwei =0
	add t2, t0, t2

jumpAdd:
	slli t0, t0, 1
	srli t1, t1, 1
	addi a0, a0,1

	blt a0, a1, loop

	bge s3,zero, out #s3 <0 qvfan
	neg t2,t2
out:
mv a0, t2
li a7, 1
ecall

li a7, 10
ecall