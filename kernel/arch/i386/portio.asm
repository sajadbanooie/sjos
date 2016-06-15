global read_port
global read_port_w
global write_port
global write_port_w
read_port:
	mov edx, [esp + 4]
	in al, dx	
	ret

write_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret
write_port_w:
	mov   edx, [esp + 4]    
	mov   ax, [esp + 4 + 4]  
	out   dx, ax  
	ret
read_port_w:
	mov edx, [esp + 4]
	in ax, dx	
	ret

