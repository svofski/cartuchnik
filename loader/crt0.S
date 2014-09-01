;;;
;;; Copyright 2006, 2007, 2008, 2009 by Brian Dominy <brian@oddchange.com>
;;; ported to Vectrex, 2013 by Frank Buss <fb@frank-buss.de>
;;;
;;; This file is part of GCC.
;;;
;;; GCC is free software; you can redistribute it and/or modify
;;; it under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 3, or (at your option)
;;; any later version.
;;;
;;; GCC is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.

;;; You should have received a copy of the GNU General Public License
;;; along with GCC; see the file COPYING3.  If not see
;;; <http://www.gnu.org/licenses/>.

		; Declare external for main()
		.globl _main

#define __STACK_TOP 0xcbea

		; Declare all linker sections, and combine them into a single bank
		.bank	prog
		.area	.text  (BANK=prog)
		.area .data  (BANK=prog)
		.area .ctors (BANK=prog)
		.word 0
		.area .bss   (BANK=prog)
__bss_start:
	    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		;;;
		;;; cartridge init block
		;;;
 	    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		.area	.text
		.ascii "g GCE 2014"	; cartrige id and year
		.byte 0x80			; string end
		.word music
		.byte 0xf8, 0x50, 0x20, -0x40	; height, width, rel y, rel x
		.ascii "VECTREXADOR"	; game title
		.byte 0x80			; string end
		.byte 0				; header end

	    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		;;;
		;;; __start : Entry point to the program
		;;;
	    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		.area	.text
		.globl __start
__start:
		lds #__STACK_TOP

		ldu #__STACK_TOP
		ldx #0
__clear_bss_loop:
		stx ,--u
		cmpu #__bss_start
		beq __clear_done
		bra __clear_bss_loop
__clear_done:

; TODO: crash
	;; Call any "initializer" functions
;	ldu	#s_.ctors
__ctors_loop:
;	ldy	,u++
;	cmpy	#0
;	beq	__ctors_done
;	jsr	,y
;	bra	__ctors_loop
__ctors_done:

		;; Call the main function.  The exit code will
		;; be returned in the X register, unless compiled
		;; with -mdret, in which case it comes back in D.
		jsr	_main
		jmp	_exit

music:
	    .word   0xfee8
	    .word   0xfeb6
	    .byte   0x0, 0x80
	    .byte   0x0, 0x80


	   	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		;;;
		;;; __exit : Exit point from the program
		;;; There is no exit for Vectrex, infinite loop
		;;;
	   	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		.area	.text
	 	.globl __exit
__exit:
		bra	__exit


        ;;;
        ;;; __crt0_vector : Default handler for interrupts
        ;;;
        .area   .text
___crt0_vector:
        ;; The default behavior is to simply ignore all
        ;; non-reset interrupts.
        rti
        
        ;;;
        ;;; vector : The interrupt vector table
        ;;; The linker will ensure that this gets loaded at address 0xFFF0.
        ;;;
        .area vector
vectors:
        .word ___crt0_vector
        .word ___crt0_vector
        .word ___crt0_vector
        .word ___crt0_vector
        .word ___crt0_vector
        .word ___crt0_vector
        .word ___crt0_vector
        .word __start

		.end __start

