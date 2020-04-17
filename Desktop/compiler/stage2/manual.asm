SECTION .data
inputi  db "Enter an integer value:",00h
output db "Output:",00h
formatstring db "%s"
newline db 0Ah,00h
formatint db "%hi"

SECTION .text
global main
extern printf
extern scanf

main:
    call driver    

    mov rdi, formatstring
    mov rsi, newline                
    xor rax, rax
    call printf

    MOV RAX, 60
    XOR RDI, RDI
    syscall
    
driver:
    push rbp
    mov rbp, rsp

    sub rsp, 16            ; curr offset

    push rbp
    mov word[rbp-8], 5
    mov word[rbp-10], 9

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

    mov bx, word[rbp-2]
    mov ax, word[rbp-4]
    imul ax, word[rbp-10]
    add bx, ax
    mov ax, word[rbp-8]
    sub ax, word[rbp-10]
    imul ax, word[rbp-4]
    add bx, ax

    mov ax, word[rbp-8]
    imul ax, 2
    add bx, ax
    mov ax, word[rbp-10]
    imul ax, word[rbp-2]
    sub bx, ax
    mov word[rbp-6], bx

    mov rdi, formatstring
    mov rsi, output                
    xor rax, rax 
    call printf

    mov rdi, formatint
    xor rsi, rsi
    mov si, word[rbp-6]        
    xor rax, rax 
    call printf


    pop rsp
    pop rbp
   

    ret