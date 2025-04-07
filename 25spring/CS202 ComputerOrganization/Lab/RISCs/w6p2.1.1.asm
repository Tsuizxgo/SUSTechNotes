    .data
m1:     .half 8      # multiplicand
m2:     .half -9     # multiplier

    .text
    .globl main
main:
    # 读取被乘数和乘数
    lh t0, m1        # t0 = multiplicand (8)
    lh t1, m2        # t1 = multiplier (-9)
    add t2, zero, zero  # 结果寄存器 t2 = 0

    # 处理乘数的符号，取其绝对值
    mv s3, t1        # 复制 t1 到 s3
    bge t1, zero, no_negate_t1
    neg t1, t1       # 如果 t1 < 0，取反
no_negate_t1:

    # 初始化循环计数器
    li a0, 0         # 迭代次数
    li a1, 16        # 16-bit 乘法

loop:
    andi s2, t1, 1    # 检查乘数最低位
    beqz s2, skip_add
    add t2, t2, t0   # 如果最低位为1，则加上被乘数

skip_add:
    slli t0, t0, 1   # 被乘数左移一位
    srli t1, t1, 1   # 乘数右移一位

    addi a0, a0, 1   # 迭代次数加1
    blt a0, a1, loop # 若未达到 16 轮，继续循环

    # 如果原始乘数 s3 是负数，则结果取反
    bge s3, zero, no_negate_result
    neg t2, t2       # 结果取反
no_negate_result:

    # 打印结果
    mv a0, t2
    li a7, 1
    ecall

    # 退出程序
    li a7, 10
    ecall
