.global load_gdt

load_gdt:
gdtr dw 0   # For limit storage
     dd 0    # For base storage
 
setGdt:
   mov  %AX, [%esp + 4]
   mov  [gdtr], %AX
   mov  %EAX, [%ESP + 8]
   mov  [gdtr + 2], %EAX
   lgdt [gdtr]
   ret