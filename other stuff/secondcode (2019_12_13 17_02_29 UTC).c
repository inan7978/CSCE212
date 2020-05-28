i = $s0
j = $s1
A = $s2

A[2] = i +j;

add $t0, $s0, $s1
sw $t0, 8($s2)

addi $t1, $s2, 8
sw $t0, 0($t1)

A[i] = i + j;

$t0 = i +j
$t1 = i * 4
$t2 = A + (i * 4)

add $t0, $s0, $s1
s11 $t1, $s0, 2 #multiply i by 4
add $t2, $t1, $s2 #memory address for A and adding i*4
sw $t0, 8($t2)
shift left
0011 -> 3 #* 2^0
0110 -> 6 #* 2^1
1100 -> 12 #* 2^2
