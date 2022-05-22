    .set MAGIC, 0x1BADB002          # badboot magic number
    .set ALIGN, 1 << 0              # align modules on page boundary
    .set MEMINFO, 1 << 1             # memory map
    .set FLAGS, ALIGN | MEMINFO     # multiboot flag
    .set CHECKSUM, -(MAGIC + FLAGS) # checksum to prove multiboot

.section .multiboot                 # multiboot header for GRUB to check
    .align 4                            # aligned 4 bytes
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .bss                       # stack allocation 
    .align 16                           # aligned 16 bytes
stack_bottom:
    .skip 16384                         # 16 kb
stack_top:

.section .text
    .global boot                    # where the bootloader will jump to
    .extern kernel_main             # reference external function
boot:
    mov $stack_top, %esp            # make stack pointer point to top of stack
    call kernel_main

    # shouldn't ever reach here but infinite loop if it does
    cli
1:  hlt
    jmp 1b

    # set size of boot symbol to be the size from boot label to end
    .size boot, . - boot
