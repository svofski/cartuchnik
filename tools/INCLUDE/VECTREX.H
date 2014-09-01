#ifndef VECTREX_H
#define VECTREX_H

/* This file describes library routines that can be used from the
 * C code.
 *
 * Vectrex bios routines are mapped to C-Makros, so that they can be
 * called efficiently.
 *
 * GCC uses certain registers for internal book keeping, we must be
 * aware of these registers, so that we don't clobber them with
 * our asm 'bios' calls.
 *
 * I use makros to check this out and wrap the calls in push/puls if
 * neccesary.
 *
 * The main problem register is the gcc FRAME_POINTER_REGISTER.
 * In the 'usual' gcc m6809 compiler this used to be the U register,
 * I changed that to Y register. The Y register access need in
 * general MORE cycles than the U register. BUT the generated code
 * gets shorter and faster if we do NOT use any framepointer at all.
 * gcc option: -fomit-frame-pointer
 * The problem is, that even if we tell gcc to omit the frame pointer,
 * it seems to have problems (or I did something wrong in the m6809 files)
 * with keeping track of the frame_pointer_register. Even if we omit it,
 * gcc assumes that the frame_pointer_register does only change its contents,
 * if it does so by itself (gcc).
 * So if we know that out asm code changes the frame_pointer_register, we
 * must make sure that when we return to our 'normal' course of action
 * the framepointer is restored to its previous state.
 * The below defines and makros assume that it is possible
 * to switch to another framepointer, but that is ONLY possible if
 * you recompile the compiler (gcc). It expects defines, as to what register
 * is used as framepointer, three possible choices:
 * FRAME_Y (is default)
 * FRAME_X
 * FRAME_U (was default)
 * Y register seems to be a really good choice for vectrex, because it
 * is seldom used by the BIOS, so we don't have to save it often.
 *
 * The gcc option: -mfixed-regs
 * Tells the compiler to assume, that no registers are available over
 * function calls.
 *
 *
 *
 *
 *
 */

// save any registers used in asm when FIXED_REGS_NO_FRAME is set
// BUT the frame pointer.
// even if we say that no frame pointer should be used, gcc thinks
// it should be immune to any changes...
//
// only needed if the asm DOES change the reg...

/* default to FRAME_Y */
#ifndef FRAME_Y
#ifndef FRAME_U
#ifndef FRAME_X
#define FRAME_Y
#endif
#endif
#endif

#ifdef FRAME_Y
#define save_frame_y() asm("pshs \ty \t; save y register");
#define restore_frame_y() asm("puls \ty \t; save y register");
#define save_frame_x() ;
#define restore_frame_x() ;
#define save_frame_u() ;
#define restore_frame_u() ;
#endif
#ifdef FRAME_U
#define save_frame_u() asm("pshs \tu \t; save u register");
#define restore_frame_u() asm("puls \tu \t; save u register");
#define save_frame_x() ;
#define restore_frame_x() ;
#define save_frame_y() ;
#define restore_frame_y() ;
#endif
#ifdef FRAME_X
#define save_frame_x() asm("pshs \tx \t; save x register");
#define restore_frame_x() asm("puls \tx \t; save x register");
#define save_frame_y() ;
#define restore_frame_y() ;
#define save_frame_u() ;
#define restore_frame_u() ;
#endif

#define true (1==1)
#define false (1==0)

#define Vec_Music_Flag  0xC856   /* Music active flag ($00=off $01=start $80=on) */
#define Vec_Dot_Dwell   0xC828   /* Dot dwell time */

#define SCRAMBLE_MUSIC ((unsigned char *)(0xFDD3))
#define CRAZY_COASTER ((unsigned char *)(0xFD0D))
#define BERZERK ((unsigned char *)(0xFD1D))
#define SOLAR_QUEST ((unsigned char *)(0xFE38))

static unsigned char __A;
static unsigned char __B;
static short __D;
static short __X;
static short __Y;
static short __U;
/* FRAME_POINTER destroys D register... might use a push instead... */
/* FRAME_POINTER is frame pointer, that <should> not be spilled by us! */
/* we don't spill any registers
   since we 'know' what we do! (otherwise allways the set register
                                would be spilled)
   attention with FRAME_POINTER register!   */
#define SET_A_REG_IM(a) asm("lda %0"::"K" ((unsigned char)a) );
#define SET_B_REG_IM(b) asm("ldb %0"::"K" ((unsigned char)b) );
#define SET_D_REG_IM(d) asm("ldd %0"::"L" ((unsigned short)d) );
#ifdef FRAME_X
#define SET_X_REG_IM(x) asm("tfr \td,x"::"d" ((unsigned short)x):"d" );
#else
#define SET_X_REG_IM(x) asm("ldx %0"::"L" ((unsigned short)x) );
#endif
#ifdef FRAME_Y
#define SET_Y_REG_IM(y) asm("tfr \td,y"::"d" ((unsigned short)y):"d" );
#else
#define SET_Y_REG_IM(y) asm("ldy %0"::"L" ((unsigned short)y) );
#endif
#ifdef FRAME_U
#define SET_U_REG_IM(u) asm("tfr \td,u"::"d" ((unsigned short)u):"d" );
#else
#define SET_U_REG_IM(u) asm("ldu %0"::"L" ((unsigned short)u) );
#endif
/* we don't spill any registers
   since we 'know' what we do! (otherwise allways the set register
                                would be spilled)
   attention with FRAME_POINTER register!   */
#define SET_A_REG(a) asm(""::"A" ((unsigned char)a));
#define SET_B_REG(b) asm(""::"B" ((unsigned char)b));
#define SET_D_REG(d) asm(""::"d" ((unsigned short)d));
#ifdef FRAME_X
#define SET_X_REG(x) asm("tfr \td,x"::"d" ((unsigned short)x):"d");
#else
#define SET_X_REG(x) asm(""::"x" ((unsigned short)x));
#endif
#ifdef FRAME_Y
#define SET_Y_REG(y) asm("tfr \td,y"::"d" ((unsigned short)y):"d");
#else
#define SET_Y_REG(y) asm(""::"y" ((unsigned short)y));
#endif
#ifdef FRAME_U
#define SET_U_REG(u) asm("tfr \td,u"::"d" ((unsigned short)u):"d");
#else
#define SET_U_REG(u) asm(""::"u" ((unsigned short)u));
#endif

/* FRAME_POINTER destroys D register... might use a push instead... */
/* FRAME_POINTER is frame pointer, that <should> not be spilled by us! */
#define GET_A_REG() asm("":"=A" ((unsigned char) __A));
#define GET_B_REG() asm("":"=B" ((unsigned char) __B));
#define GET_D_REG() asm("":"=d" ((unsigned short) __D));
#ifdef FRAME_X
#define GET_X_REG() asm("tfr \tx,d":"=d" ((unsigned short) __X)::"d");
#else
#define GET_X_REG() asm("":"=x" ((unsigned short) __X));
#endif
#ifdef FRAME_Y
#define GET_Y_REG() asm("tfr \ty,d":"=d" ((unsigned short) __Y)::"d");
#else
#define GET_Y_REG() asm("":"=y" ((unsigned short) __Y));
#endif
#ifdef FRAME_U
#define GET_U_REG() asm("tfr \tu,d":"=d" ((unsigned short) __U)::"d");
#else
#define GET_U_REG() asm("":"=u" ((unsigned short) __U));
#endif

#define read_ram(mem) ((unsigned char)(*((volatile unsigned char *) ((void *)((volatile unsigned short)(mem))))))
#define write_ram(mem, value) ((*((volatile unsigned char *)(mem))) = ((volatile unsigned char)(value)))

/* NOTE:
 * while calculating address, operands, values... allways make sure
 * D is calculated last, since D is the general Data register which might
 * be destroyed by evaluating other expressions.
 *
 * Likewise, allway calculate A prior to B, since B is the
 * 'more general' register. It is used for every byte evaluation, since
 * there is only one DATA register (D = A+B).
 * If a Data expression is byte size, allways register B is used!
 *
 * clobber constraints seem not to work for FRAME_REGISTER -> save FRAME_REGISTER yourself!
 *
 * !!!!
 erwperw
 */

/* ... dp -> d0 */
#define wait_recal() {save_frame_x()\
                     asm("jsr \t0HF192 \t; wait_recal");\
                     restore_frame_x()}
/* ... */
#define intensity(i) asm("jsr \t0HF2AB \t; intensity_a"::"A" ((unsigned char)(i)):"a")
/* dp = d0 */
#define move_to(x,y) asm("jsr \t0HF312 \t; move_to_d"::"A" ((unsigned char)(y)),"B" ((unsigned char)(x)):"a","b","d")
/* dp = d0 */
#define draw_line(x,y) {save_frame_x()\
                     asm("jsr \t0HF3DF \t; draw_d"::"A" ((unsigned char)(y)),"B" ((unsigned char)(x)):"a","b","d","x");\
                     restore_frame_x()}
/* ... */
#define set_scale(scale) asm("sta \t0HD004 \t; VIA timer 1 count register lo (scale factor)"::"A" ((unsigned char)(scale)))

/* dp = d0 */
#ifdef FRAME_U
#define print_str(x,y,string) {save_frame_u() \
                              asm("leau \t,%02 \t; get string address to u\n\tjsr \t0HF37A \t; print_str_d"\
                                  ::"A" ((unsigned char)(y)),\
                                    "B" ((unsigned char)(x)),\
                                    "x" ((unsigned char *)string)\
                                   :"a","b","d","x","u"); \
                              restore_frame_u()}
#else
#define print_str(x,y,string) {save_frame_x() \
                              asm("jsr \t0HF37A \t; print_str_d"\
                                  ::"A" ((unsigned char)(y)),\
                                    "B" ((unsigned char)(x)),\
                                    "u" ((unsigned char *)string)\
                                   :"a","b","d","x","u"); \
                              restore_frame_x()}
#endif
/* ... */
#define zero_beam() asm("ldb \t#0HCC \t; bitmap for...\n\tstb \t0HD00C \t; ~BLANK low and ~ZERO low")
/* dp = d0 */
#define draw_vector_list(list) \
                              {save_frame_x() \
                              asm("jsr \t0HF3CE \t; draw_vlc"::"x" ((void *)(list)):"a","b","d","x");\
                              restore_frame_x()}
/* dp = d0 */
#define draw_vector_list_pattern(list) \
                              {save_frame_x() \
                              asm("jsr \t0HF410 \t; draw_vlp"::"x" ((void *)(list)):"a","b","d","x");\
                              restore_frame_x()}
/* dp = d0 */
#define draw_vector_list_count(list, count) asm("jsr \t0HF3DA \t; draw_vl_a"::"A" ((unsigned char)(count)), "x" ((void *)(list)):"a","b","d","x")


/* dp = d0 */
#define draw_dot(x,y) \
                              {\
                              asm("jsr \t0HF2C3 \t; Dot_d"\
                                  ::"A" ((unsigned char)(y)),\
                                    "B" ((unsigned char)(x))\
                                   :"a", "b", "d");\
                              }
/* dp = d0 */
#define draw_dot_here() \
                              {\
                              asm("jsr \t0HF2C5 \t; Dot_here"\
                                   :::"a", "b", "d");\
                              }
/* ... */
#define set_dp(dp) asm("tfr \tb,dp \t; set dp to b "::"B" ((unsigned char)(dp)):"b","dp")
/* ... dp -> c8 */
#define set_dp_c8() set_dp(0xC8)
/* ... dp -> d0 */
#define set_dp_d0() set_dp(0xD0)
/* ... */
#define get_random() asm("jsr \t0HF517 \t; random":"=A"((unsigned char)(__A))::"a","b","d")
/* dp = d0 */
#define joy_digital() \
                              {save_frame_x() \
                              asm("jsr \t0HF1F8 \t; joy_digital":::"a","b","d","x");\
                              restore_frame_x()}
/* dp = d0 */
//#define read_buttons() asm("jsr \t0HF1BA \t; read_btns")
#define read_buttons()\
                              {save_frame_x() \
                              asm("lda \t#0\n\tjsr \t0HF1B4 \t; read_btns_mask":::"a","b","d");\
                              restore_frame_x()}
/* dp = c8 */
#ifdef FRAME_U
#define recalculate_music(song) {save_frame_u() \
                                asm ("leau \t,%00 \t; get song address to u\n\tjsr \t0HF687 \t; Init_Music_chk"\
                                        ::"x" ((unsigned char *)song)\
                                         :"a","b","d","x","y","u");\
                                restore_frame_u()}
#else
#define recalculate_music(song) {save_frame_x() \
                                save_frame_y() \
                                asm ("jsr \t0HF687 \t; Init_Music_chk"\
                                        ::"u" ((unsigned char *)song)\
                                         :"a","b","d","x","y","u");\
                                restore_frame_y()\
                                restore_frame_x()}
#endif
/* dp = d0 */
#define do_sound() {save_frame_x() \
                   save_frame_u() \
                   asm("jsr \t0HF289 \t; do_sound" \
                       :::"a","b","d","x", "u"); \
                   restore_frame_u() \
                   restore_frame_x()}





/* dp = d0 */
#ifdef FRAME_U
#define do_explosion(explosion_data) {save_frame_u() \
                              asm("leau \t,%02 \t; get address to u\n\tjsr \t0HF92E \t; Explosion_Snd"\
                                   ::"x" ((unsigned char *)explosion_data)\
                                    :"a","b","d","x","u"); \
                              restore_frame_u()}
#else
#define do_explosion(explosion_data) {save_frame_x() \
                              asm("jsr \t0HF92E \t; Explosion_Snd"\
                                  ::"u" ((unsigned char *)explosion_data)\
                                   :"a","b","d","x","u"); \
                              restore_frame_x()}
#endif

#define clear_sound() {save_frame_x() \
                              asm("jsr \t0HF272 \t; Clear_Sound"\
                                   :::"a","b","d","x"); \
                              restore_frame_x()}



/* ... */
#define enable_joystick_1x() asm("lda \t#1 \t; enable\n\tsta \t0HC81F \t; Vec_Joy_Mux_1_X":::"a")
/* ... */
#define disable_joystick_1x() asm("lda \t#0 \t; disable\n\tsta \t0HC81F \t; Vec_Joy_Mux_1_X":::"a")
/* ... */
#define enable_joystick_1y() asm("lda \t#3 \t; enable\n\tsta \t0HC820 \t; Vec_Joy_Mux_1_Y":::"a")
/* ... */
#define disable_joystick_1y() asm("lda \t#0 \t; disable\n\tsta \t0HC820 \t; Vec_Joy_Mux_1_Y":::"a")
/* ... */
#define enable_joystick_2x() asm("lda \t#5 \t; enable\n\tsta \t0HC821 \t; Vec_Joy_Mux_2_X":::"a")
/* ... */
#define disable_joystick_2x() asm("lda \t#0 \t; disable\n\tsta \t0HC821 \t; Vec_Joy_Mux_2_X":::"a")
/* ... */
#define enable_joystick_2y() asm("lda \t#7 \t; enable\n\tsta \t0HC822 \t; Vec_Joy_Mux_2_Y":::"a")
/* ... */
#define disable_joystick_2y() asm("lda \t#0 \t; disable\n\tsta \t0HC822 \t; Vec_Joy_Mux_2_Y":::"a")

#define joystick1_x ((signed char) (read_ram(0xc81b)))
#define joystick1_y ((signed char) (read_ram(0xc81c)))
#define joystick2_x ((signed char) (read_ram(0xc81d)))
#define joystick2_y ((signed char) (read_ram(0xc81e)))

#define joystick1_button1_toggle ((unsigned char)(((unsigned char)read_ram(0xc812)) == ((unsigned char) 0x01)))
#define joystick1_button2_toggle ((unsigned char)(((unsigned char)read_ram(0xc813)) == ((unsigned char) 0x02)))
#define joystick1_button3_toggle ((unsigned char)(((unsigned char)read_ram(0xc814)) == ((unsigned char) 0x04)))
#define joystick1_button4_toggle ((unsigned char)(((unsigned char)read_ram(0xc815)) == ((unsigned char) 0x08)))
#define joystick2_button1_toggle ((unsigned char)(((unsigned char)read_ram(0xc816)) == ((unsigned char) 0x10)))
#define joystick2_button2_toggle ((unsigned char)(((unsigned char)read_ram(0xc817)) == ((unsigned char) 0x20)))
#define joystick2_button3_toggle ((unsigned char)(((unsigned char)read_ram(0xc818)) == ((unsigned char) 0x40)))
#define joystick2_button4_toggle ((unsigned char)(((unsigned char)read_ram(0xc819)) == ((unsigned char) 0x80)))

#define joystick1_button1 ((unsigned char)(((unsigned char)read_ram(0xC80F)) & ((unsigned char) 0x01)))
#define joystick1_button2 ((unsigned char)(((unsigned char)read_ram(0xC80F)) & ((unsigned char) 0x02)))
#define joystick1_button3 ((unsigned char)(((unsigned char)read_ram(0xC80F)) & ((unsigned char) 0x04)))
#define joystick1_button4 ((unsigned char)(((unsigned char)read_ram(0xC80F)) & ((unsigned char) 0x08)))
#define joystick2_button1 ((unsigned char)(((unsigned char)read_ram(0xC80F)) & ((unsigned char) 0x10)))
#define joystick2_button2 ((unsigned char)(((unsigned char)read_ram(0xC80F)) & ((unsigned char) 0x20)))
#define joystick2_button3 ((unsigned char)(((unsigned char)read_ram(0xC80F)) & ((unsigned char) 0x40)))
#define joystick2_button4 ((unsigned char)(((unsigned char)read_ram(0xC80F)) & ((unsigned char) 0x80)))

typedef signed char* VECTOR_LIST;


// vectrex 'C' - lib
extern unsigned char random();












#endif VECTREX_H



/*

Constraint classes:
    "q"             * 8-bit (byte (HI)) data (a, b, D)
    "d"             * 16-bit (word (SI)) data (only D)
    "a"             * 16-bit addresses S, PC, X, Y, U
    "g"             * general S, PC, X, Y, U , A, B, D
                    * + typical gcc contraints
    "A"             * A register
    "B"             * B register
    "x"             * x register (when framepointer mostly forbidden due to framepointer use...)
    "y"             * y register (when framepointer mostly forbidden due to framepointer use...)
    "u"             * u register (when framepointer mostly forbidden due to framepointer use...)

--------------------------------------------------------------
   The letters I, J, K, L and M in a register constraint string
   can be used to stand for particular ranges of immediate operands.
   This macro defines what the ranges are.
   C is the letter, and VALUE is a constant value.
   Return 1 if VALUE is in the range specified by C.

   For the 6809, J, K, L are used for indexed addressing.
   `I' is used for shift counts which can only be equal to 1.
   `J' is used for the 5-bit offsets.
   `K' is used for the 8-bit offsets.
   `L' is used for the range of signed numbers that fit in 16 bits.
--------------------------------------------------------------


Clobber register names:
"d", "x", "y", "u", "s", "p","a", "b", "cc","dp"


   3. It is possible that if an input dies in an insn, reload might
      use the input reg for an output reload.  Consider this example:

                asm ("foo" : "=t" (a) : "f" (b));

      This asm says that input B is not popped by the asm, and that
      the asm pushes a result onto the reg-stack, ie, the stack is one
      deeper after the asm than it was before.  But, it is possible that
      reload will think that it can use the same reg for both the input and
      the output, if input B dies in this insn.

        If any input operand uses the "f" constraint, all output reg
        constraints must use the "&" earlyclobber.

      The asm above would be written as

                asm ("foo" : "=&t" (a) : "f" (b));


*/