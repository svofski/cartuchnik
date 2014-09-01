/*
 * Include some standard vectrex functions first!
 */
#include <vectrex.h>

/*
 * Non standard include :-!, assembler scrolling routine
 */
#include <scroll.h>

/*
 * Some defines, Maximal brightness is $7f, highest not set!
 * Max Scale would be $ff, well here we take only $f0!
 */
#define MAX_BRIGHTNESS (0x7f)
#define MAX_SCALE (0xf0)

/*
 * If you declare a function 'static inline' it is pretty much sure that
 * the compiler will inline it completely, the function will not
 * appear in any way in the module.
 *
 * If you leave out the static, the compiler assumes it might be used
 * globally, and thus leaves the function in the code, even if
 * it is inlined everywhere!
 */
/*
 * This Funktion handles all startup code, needed for vectrex to work
 * correctly, recallibrating the beam and making sure that some sound
 * is played (if wanted).
 */
static inline void start_one_vectrex_round(void)
{
  wait_recal();                       /* sets this up allright... */
}

/*
 * A simple setup routine, enables/disables the joystick, and makes sure
 * that the button state is read correctly...
 */
static inline void setup(void)
{
  read_buttons();                     /* read it twice, I had trouble doing it once only :-( */
  wait_recal();                       /* one round */
  read_buttons();
  wait_recal();                       /* one round */
}

const unsigned char text[] =
"A REALLY SMALL VECTREX DEMO. FEATURING A\
 SCROLLER WRITTEN IN ASSEMBLER...            ";
static inline void intro(void)
{
  scr_y = -50;                  /* y position of scroller */
  scr_lbnd= -60;                /* left boundery */
  scr_rbnd= 60;                 /* right boundery */
  scr_sped=-1;                  /* speed, must be negativ, the lower the faster */
  scr_ints=MAX_BRIGHTNESS;      /* brightness of scrolling */

  scroll_init(text);            /* initialize scroller with text */
  do
  {
    start_one_vectrex_round();  /* initialize vectrex for this round */
    intensity(MAX_BRIGHTNESS);  /* set some brightness */
    set_scale(MAX_SCALE);       /* set the scale for movement */
    print_str(-30,100, "DEMO 4"); /* a message! */

    scr_step();                 /* do one scroll step */
    read_buttons();             /* read buttons, if pressed... finish here */
  }
  while (!joystick1_button1);   /* was a button pressed ? */
}

/*
 * Our main function we start of here...
 * we should make sure that we never return from here, or vectrex will
 * be surely bothered!
 */
int main(void)
{
  setup();                            /* setup our program */
  while (true)                        /* never to return... */
  {
    intro();                          /* do the intro over and over again :-( */
  } /* while (true) */                /* joystick information is up to date */
}

/* END OF FILE */
