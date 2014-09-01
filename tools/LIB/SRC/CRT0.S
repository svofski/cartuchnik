        .module  main
        .area    __header (ABS)
        .org     0
        .ascii   "g GCE 1998"
        .db      0H80
        .dw      0HFD0D
        .db      0HF8, 0H50, 0H20, (256-0H36)
        .ascii   "VECTREX C"
        .db      0H80
        .db      0HF8, 0H50, 0H5, (256 -0H30)
        .ascii   "GCC 6809"
        .db      0H80
        .db      0

        .globl  start
start:
        .globl  ___main
        jmp     _main
___main:
        rts
        .globl  ___header_end
___header_end:
        .area __data
        .area __code
