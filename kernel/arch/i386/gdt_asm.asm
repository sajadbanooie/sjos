global setgdt
global reloadseg
global settss
extern gp
setgdt:
   LGDT  [gp]
   RET


reloadseg:
   ; Reload CS register containing code selector:
   JMP   0x08:.reload_CS 
; 0x08 points at the new code selector
   
.reload_CS:
   ; Reload data segment registers:
   MOV   AX, 0x10 ; 0x10 points at the new data selector
   MOV   DS, AX
   MOV   ES, AX
   MOV   FS, AX
   MOV   GS, AX
   MOV   SS, AX
   RET

settss:
	cli
	mov eax, 0x2b
	ltr ax
	sti
	ret
