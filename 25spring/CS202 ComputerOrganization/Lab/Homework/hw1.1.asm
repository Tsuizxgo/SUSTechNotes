.data 
	s: .space 1024
	
.text
	main: li a7,8
	    la a0,s
	    li a1,1024
	    ecall
	  li a7,4
	  ecall
	  li a7,10
	  ecall 