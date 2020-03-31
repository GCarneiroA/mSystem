.code32
.intel_syntax noprefix
.text

.global start
start:
    lea     esp, sys_stack      # Configura a pilha.
    call    _start_kernel       # Chama a função em C.


# Aqui está a definição da nossa seção BSS.
# No momento, vamos usá-lo apenas para armazenar a pilha.
# Lembre-se de que uma pilha realmente cresce para baixo,
# portanto declaramos o tamanho dos dados
# antes de declarar o identificador '_sys_stack'
.section .bss
    .lcomm buff, 0x1000          # Reservar 4KB de dados

sys_stack:

.section .data
    sec_id:     .ascii "DATA SECTION"
