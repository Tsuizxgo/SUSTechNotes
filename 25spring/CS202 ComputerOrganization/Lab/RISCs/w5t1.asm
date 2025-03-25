.include "macro_print_str.asm"
.data
dvalue1: .word 0x02
dvalue2: .word 0x0f
.text
lw t1, dvalue1
lw t2, dvalue2
add t0, t1, t2
slti t3, t2, 0
slt t4, t0, t1 # add two values
# t3 = (t2 < 0)
# t4 = (t0 < t1), thst is, (t1 + t2 < t1)
mv a0, t0
li a7, 1
ecall
bne t3, t4, overflow # print the sum
# overflow if (t2 < 0) && (t1 + t2 >= t1)
# or if (t2 >= 0) && (t1 + t2 < t1)
print_string("\nNo overflow occured.")
jal exit
overflow:
print_string("\nOne overflow occured.")
exit:
end