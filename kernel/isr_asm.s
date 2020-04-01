.code32
.intel_syntax noprefix
.text

.global _isr0
.global _isr1
.global _isr2
.global _isr3
.global _isr4
.global _isr5
.global _isr6
.global _isr7
.global _isr8
.global _isr9
.global _isr10
.global _isr11
.global _isr12
.global _isr13
.global _isr14
.global _isr15
.global _isr16
.global _isr17
.global _isr18
.global _isr19
.global _isr20
.global _isr21
.global _isr22
.global _isr23
.global _isr24
.global _isr25
.global _isr26
.global _isr27
.global _isr28
.global _isr29
.global _isr30
.global _isr31

.macro mISRNoArg num
    push 0
    push \num
    jmp isr_common_stub
.endm

.macro mISRArg num
    push \num
    jmp isr_common_stub
.endm

_isr0:  mISRNoArg  0  # Divide-by-zero exception
_isr1:  mISRNoArg  1  # Debug exception
_isr2:  mISRNoArg  2  # Non Maskable Interrupt Exception
_isr3:  mISRNoArg  3  # Breakpoint Exception
_isr4:  mISRNoArg  4  # Into Detected Overflow Exception
_isr5:  mISRNoArg  5  # Out of Bounds Exception
_isr6:  mISRNoArg  6  # Invalid Opcode Exception
_isr7:  mISRNoArg  7  # No Coprocessor Exception
_isr8:  mISRArg    8  # Double Fault Exception
_isr9:  mISRNoArg  9  # Coprocessor Segment Overrun Exception
_isr10: mISRArg   10  # Bad TSS Exception
_isr11: mISRArg   11  # Segment Not Present Exception
_isr12: mISRArg   12  # Stack Fault Exception
_isr13: mISRArg   13  # General Protection Fault Exception
_isr14: mISRArg   14  # Page Fault Exception
_isr15: mISRNoArg 15  # Unknown Interrupt Exception
_isr16: mISRNoArg 16  # Coprocessor Fault Exception
_isr17: mISRNoArg 17  # Alignment Check Exception (486+)
_isr18: mISRNoArg 18  # Machine Check Exception (Pentium/586+)
_isr19: mISRNoArg 19  # Reserved
_isr20: mISRNoArg 20  # Reserved
_isr21: mISRNoArg 21  # Reserved
_isr22: mISRNoArg 22  # Reserved
_isr23: mISRNoArg 23  # Reserved
_isr24: mISRNoArg 24  # Reserved
_isr25: mISRNoArg 25  # Reserved
_isr26: mISRNoArg 26  # Reserved
_isr27: mISRNoArg 27  # Reserved
_isr28: mISRNoArg 28  # Reserved
_isr29: mISRNoArg 29  # Reserved
_isr30: mISRNoArg 30  # Reserved
_isr31: mISRNoArg 31  # Reserved

isr_common_stub:
    pusha
    push    ds
    push    es
    push    fs
    push    gs
    mov     ax, 0x10   # Load the Kernel Data Segment descriptor!
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     eax, esp   # Push us the stack
    push    eax
    lea     eax, _fault_handler
    call    eax        # A special call, preserves the 'eip' register
    pop     eax
    pop     gs
    pop     fs
    pop     es
    pop     ds
    popa
    add     esp, 8     # Cleans up the pushed error code and pushed ISR number
    iret             # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
