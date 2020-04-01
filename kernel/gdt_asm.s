.code32
.intel_syntax noprefix
.text

.extern _gdtp
.global _gdt_flush

_gdt_flush:
    lgdt    _gdtp
    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    jmp     0x08:flush2

flush2:
    ret
