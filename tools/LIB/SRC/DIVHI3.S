;       divhi3
;       calling: (left / right)
;               push left
;               push right
;               jsr  _divhi3
        .module divhi3.s
        .area   __code

        .globl _divhi3
_divhi3:
        ldd     2,s
        pshs    d
        ldd     6,s
        jsr     sdiv
        rts

;       signed divide
;       calling: (left / right)
;               push left
;               ldd right
;               jsr sdiv
;       result in d, arg popped.
;
        left=6
        right=2
        sign=1
        count=0
        return=4
        CARRY=1
        .globl prabs
sdiv:   leas    -4,s
        std     right,s
        bne     nozero
        swi2
        .byte   0xff
nozero: jsr     prabs
div:    clr     count,s         ; prescale divisor
        inc     count,s
mscl:   inc     count,s
        aslb
        rola
        bpl     mscl
        std     right,s
        ldd     left,s
        clr     left,s
        clr     left+1,s
div1:   subd    right,s         ; check subtract
        bcc     div2
        addd    right,s
        andcc   #~CARRY
        bra     div3
div2:   orcc    #CARRY
div3:   rol     left+1,s        ; roll in carry
        rol     left,s
        lsr     right,s
        ror     right+1,s
        dec     count,s
        bne     div1
        ldd     left,s
        tst     sign,s          ; sign fiddle
        beq     nochg
        nega
        negb
        sbca    #0
nochg:  std     right,s         ; move return addr
        ldd     return,s
        std     left,s
        ldd     right,s
        leas    6,s
        rts

;       prabs.  converts both args to unsigned, and
;       remembers result sign as sign a eor sign b
;       used only by divide support
;       result d contains right, sign is non-zero
;       if result (from divide) should be negative.
;
;
        left=8
        right=4
        sign=3
prabs:  clr     sign,s
        ldd     left,s
        bge     tryr
        nega
        negb
        sbca    #0
        std     left,s
        inc     sign,s
tryr:   ldd     right,s
        bge     done
        nega
        negb
        sbca    #0
        dec     sign,s
        std     right,s
done:   rts
