.code32
.intel_syntax noprefix
.text

.extern _idtp
.global _idt_load
_idt_load:
    lidt _idtp
    ret

# .section .data
  #  _idtp:       .byte 1,2,3,4,5,6
