SECTION .data
inputi  db "Input: Enter an integer value",00h
inputb  db "Input: Enter a boolean value",00h
output db "Output:",00h
formatstring db "%s"
newline db 0Ah,00h
formatint db "%hi",00h
formatbool db "%hi",00h
true db "true",00h
false db "false",00h
range1 dw 0
range2 dw 0
base dq 0
formatarray db "Input: Enter %hi elements of %s type for range %hi to %hi ",0Ah,00h 
INTEGER db "integer",00h
BOOLEAN db "boolean",00h
booltemp dw 0

SECTION .text
global main
extern printf
extern scanf

main:
   call driver

   mov rax, 60
   xor rdi, rdi
   syscall

driver:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    push rbp

    mov rdi, formatstring
    mov rsi, inputb
    xor rax, rax
    call printf

    mov rdi, formatbool
    mov rsi, rbp
    sub rsi, 13
    mov rax, 0
    call scanf

    mov rax, 5
    push rax
    pop rax
    mov rbx, rbp
    sub rbx, 8
    mov word[rbx], ax

    mov rax, 9
    push rax
    pop rax
    mov rbx, rbp
    sub rbx, 10
    mov word[rbx], ax

    mov rdi, formatstring
    mov rsi, inputi
    xor rax, rax
    call printf

    mov rdi, formatint
    mov rsi, rbp
    sub rsi, 2
    mov rax, 0
    call scanf

    mov rdi, formatstring
    mov rsi, inputi
    xor rax, rax
    call printf

    mov rdi, formatint
    mov rsi, rbp
    sub rsi, 4
    mov rax, 0
    call scanf

    mov ax, word[rbp - 2]
    push rax
    mov ax, word[rbp - 4]
    push rax
    mov ax, word[rbp - 10]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 8]
    push rax
    mov ax, word[rbp - 10]
    push rax
    pop rbx
    pop rax
    sub ax, bx
    push rax

    mov ax, word[rbp - 4]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 8]
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 10]
    push rax
    mov ax, word[rbp - 2]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    pop rbx
    pop rax
    sub ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rax
    mov rbx, rbp
    sub rbx, 6
    mov word[rbx], ax

    mov ax, word[rbp - 6]
    push rax
    mov rax, 10
    push rax
    pop rbx
    pop rax
    mov rdx, 1
    cmp ax,bx
    jg label1
    mov rdx, 0
    label1:
    push rdx

    mov ax, word[rbp - 8]
    push rax
    mov ax, word[rbp - 10]
    push rax
    pop rbx
    pop rax
    mov rdx, 1
    cmp ax,bx
    jle label2
    mov rdx, 0
    label2:
    push rdx

    mov ax, word[rbp - 2]
    push rax
    mov ax, word[rbp - 4]
    push rax
    pop rbx
    pop rax
    mov rdx, 1
    cmp ax,bx
    jl label3
    mov rdx, 0
    label3:
    push rdx

    mov ax, word[rbp - 13]
    push rax
    pop rbx
    pop rax
    and ax, bx
    push rax

    pop rbx
    pop rax
    and ax, bx
    push rax

    pop rbx
    pop rax
    or ax, bx
    push rax

    pop rax
    mov rbx, rbp
    sub rbx, 14
    mov byte[rbx], al

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, formatint
    xor rsi, rsi
    mov si, word[rbp-6]
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline   
    xor rax, rax
    call printf

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, formatstring
    xor rsi, rsi
    mov dl, byte[rbp-13]
    mov rsi, true
    cmp dl, 1
    je label4
    mov rsi, false
    label4:
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline   
    xor rax, rax
    call printf

    pop rsp
    pop rbp
    ret

