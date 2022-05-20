.set IRQ_BASE, 0x20

.section .text

.extern _ZN17interrupt_manager16handle_interruptEhj
.global _ZN17interrupt_manager24ignore_interrupt_requestEv

.macro handle_exception num 
.global _ZN17interrupt_manager18handle_exception\num\()Ev
_ZN17interrupt_manager18handle_exception\num\()Ev:
    movb $\num, (interrupt_number)
    jmp int_bottom
.endm

.macro handle_interrupt_request num 
.global _ZN17interrupt_manager28handle_interrupt_request\num\()Ev
_ZN17interrupt_manager28handle_interrupt_request\num\()Ev:
    movb $\num + IRQ_BASE, (interrupt_number)
    jmp int_bottom
.endm

handle_interrupt_request 0x00
handle_interrupt_request 0x01
handle_interrupt_request 0x0C

int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interrupt_number)
    call _ZN17interrupt_manager16handle_interruptEhj
    # addl $5, %esp
    mov %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

_ZN17interrupt_manager24ignore_interrupt_requestEv:
    iret


.data
    interrupt_number: .byte 0