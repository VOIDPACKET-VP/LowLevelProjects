option casemap:none

includelib ucrt.lib
includelib legacy_stdio_definitions.lib
includelib msvcrt.lib
includelib kernel32.lib                    


externdef printf:proc
externdef scanf:proc


.data    
    toEchoStringValue db 17 dup(0)              ; scanf output buffer (reserve 17 bytes initialized to 0, to terminate to the string)
    toEchoFmtString db "%16s", 0                ; scanf input format string (lenght is limited to 16 char or once scanf finds a space)
    toEchoOutFmt db "%s", 0                     ; print out the output of scanf


.code
main proc

    sub rsp, 20h

    lea rcx, toEchoFmtString        ; pointer to the format string
    lea rdx, toEchoStringValue      ; pointer to the buffer that will store the string that scanf will read
    call scanf
    lea rcx, toEchoOutFmt
    lea rdx, toEchoStringValue
    call printf

    add rsp, 20h
    xor rax, rax
    ret

main endp
end                             