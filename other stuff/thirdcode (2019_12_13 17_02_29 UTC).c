while(i < j)
   i++;

i = $s0
j = $s1

Loop:
    slt $t0, $s0, $s1 #$to = 1 if i<j, else $t0 =0
    beq $t0, $zero, exit
    addi $s0, $s0, 1
j Loop
exit: ...

while (i < 5)
   i++;
Loop:
      slti $t0, $s0, 5   
      beq $t0, $zero, exit
      addi $s0, $s0, 1
      J Loop
exit:...      
