;------------------------------------------
; int slen(String message)
; String length calculation function
slen:
    push    rbx
    mov     rbx, rax
 
nextchar:
    cmp     byte [eax], 0
    jz      finished
    inc     eax
    jmp     nextchar
 
finished:
    sub     eax, ebx
    pop     rbx
    ret
 
 
;------------------------------------------
; void sprint(String message)
; String printing function
sprint:
    push    rdx
    push    rcx
    push    rbx
    push    rax
    call    slen
 
    mov     rdx, rax
    pop     rax
 
    mov     rcx, rax
    mov     rbx, 1
    mov     rax, 4
    int     80h
 
    pop     rbx
    pop     rcx
    pop     rdx
    ret
 
 
;------------------------------------------
; void sprintLF(String message)
; String printing with line feed function
sprintLF:
    call    sprint
 
    push    rax         ; push eax onto the stack to preserve it while we use the eax register in this function
    mov     rax, 0Ah    ; move 0Ah into eax - 0Ah is the ascii character for a linefeed
    push    rax         ; push the linefeed onto the stack so we can get the address
    mov     rax, rsp    ; move the address of the current stack pointer into eax for sprint
    call    sprint      ; call our sprint function
    pop     rax         ; remove our linefeed character from the stack
    pop     rax         ; restore the original value of eax before our function was called
    ret                 ; return to our program
 
 
;------------------------------------------
; void exit()
; Exit program and restore resources
quit:
    mov     rbx, 0
    mov     rax, 1
    int     80h
    ret