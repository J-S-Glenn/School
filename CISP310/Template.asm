; Template.asm  -  Assembly template
; Authoer: J. Glenn		Date: 2/5/2024

; Registers available: eax, ebx, ecx, edx

.586          ;Runs 32-Bit appication
.MODEL FLAT   ;Flat memory structure is used
.STACK 4096   ; Reserve 4096-byte stack

.DATA
; Variables go here
; BYTE  -- 8 bit
; WORD  -- 16 bit
; DWORD -- 32 bit
; QWORD -- 64 bit

.CODE

main PROC
	; Main goes here
men ENDP
END