; modhi3
; calling ( left % right )
; push right
; push left
; jsr  _modhi3

        .module modhi3.s
        .area   __code

        .globl  _modhi3
_modhi3:
        ldd     2,s
        pshs    d
        ldd     6,s
        jsr     smod
        rts



;       signed mod
;       calling: (left / right)
;               push left
;               ldd right
;               jsr smod
;       result in d, arg popped.
;
        left=6
        right=2
        sign=1
        count=0
        return=4
        CARRY=1
smod:   leas    -4,s
        std     right,s
        bne     nozero
        swi2
        .byte   0xff
nozero: jsr     mrabs
mod:    clr     count,s         ; prescale divisor
        inc     count,s
mscl:   inc     count,s
        aslb
        rola
        bpl     mscl
        std     right,s
        ldd     left,s
        clr     left,s
        clr     left+1,s
mod1:   subd    right,s         ; check subtract
        bcc     mod2
        addd    right,s
        andcc   #~CARRY
        bra     mod3
mod2:   orcc    #CARRY
mod3:   rol     left+1,s        ; roll in carry
        rol     left,s
        lsr     right,s
        ror     right+1,s
        dec     count,s
        bne     mod1
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



;       mrabs.  converts both args to unsigned, and
;       remembers result sign as the sign of the left
;       argument.  (for signed modulo)
;       result d contains right, sign is non-zero
;       if result (from mod) should be negative.
;
;
        left=8
        right=4
        sign=3
mrabs:  clr     sign,s
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
        std     right,s
done:   rts
