.set MAGIC, 0x1BADB002              # badboot magic number
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernel_main
.extern call_constructors
.global loader

loader:
    mov $kernel_stack, %esp         # mov stack pointer to top of kernel
    call call_constructors
    push %eax
    push %ebx
    call kernel_main

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 4*1024*1024      # 4 MiB reserved for stack
kernel_stack:
