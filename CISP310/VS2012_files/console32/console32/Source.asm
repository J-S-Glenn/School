; Example assembly language program -- adds two numbers
; Author: R. Detmer
.586
.MODEL FLAT
.STACK 4096 ; reserve 4096-byte stack
.DATA ; reserve storage for data
number DWORD -10
sum DWORD ?
.CODE ; start of main program code
main PROC
mov eax,number ; first number in memory
add eax, 158 ; add 158
mov sum, eax ; sum to memory
mov eax, 0 ; exit with return code 0
ret
main ENDP
END ; end of source code