#ifndef SCROLL_H
#define SCROLL_H

/*
 * Include some standard vectrex functions first!
 */
#include <vectrex.h>

/*
 * The linker/assembler only supports labels up to 8 character
 * (after that it discards). I truncated the labels to take that
 * into account... but it's not so readable anymore...
 */
extern unsigned char scr_y;     /* Y-Position of scroller... */
extern unsigned char scr_lbnd;  /* left border of scroller */
extern unsigned char scr_rbnd;  /* right border of scroller */
extern unsigned char scr_sped;  /* speed 0 - -## (must be negativ) */
extern unsigned char scr_ints;  /* brightness of text */
extern void scr_init(void);     /* initialize scroller, above variables */
                                /* must be already set */
extern void scr_step(void);     /* do one scroll step, called ones per */
                                /* round */

void scroll_init(const char *atext) /* 'C' callable init, with scrolltext */
{                                   /* as parameter */
  SET_X_REG(atext);             /* set text address to reg X */
  scr_init();                   /* and call the asm init... */
}
#endif