mov r0, 2.5
store r0, [x]

load r1, [x]
load r2, [x]
mul r1, r2
mov r3, 2
add r1, r3
store r1, [x]

load r4, [x]
neg r4
mov r0, r4
call print

mov r5, 16.5
mov r6, 2
load r7, [x]
mul r6, r7
cmp r5, r6
je label0
mov r0, 0
jmp label1
label0:
mov r0, 1
label1:
call print

