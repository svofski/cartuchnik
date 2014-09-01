/*
 * Include some standard vectrex functions first!
 */
#include <vectrex.h>

/*
 * Non standard include :-!, a pacman animation...
 */
#include "pacman.h"

/*
 * Some defines, Maximal brightness is $7f, highest not set!
 * Max Scale would be $ff, well here we take only $f0!
 */
#define MAX_BRIGHTNESS (0x7f)
#define MAX_SCALE (0xf0)
#define MOVE_SCALE 0x90

/*
 * For variable variables ALLWAYS leave them uninitialized, this way
 * the compiler puts them into the BSS ram section in vectrex ram
 * area from c880 onwards.
 *
 * All non BSS memory should be declared constant!
 * (This is still leaves the option of auto variables in a
 * functiion, which will takes it needed men from the stack)
 *
 */
unsigned char *current_song;

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
  set_dp_c8();                        /* vectrex internal... dp must point */
  recalculate_music(current_song);    /* to c800, could make a function which */
  wait_recal();                       /* sets this up allright... */
  do_sound();
}

/*
 * This function sets up a piece of music to be played from the start
 * of the next round on onward...
 */
static inline void play_song(unsigned char *song)
{
  write_ram(Vec_Music_Flag, 1);       /* A makro to write to a specific memory */
  current_song = song;                /* address */
}

/*
 * A simple setup routine, enables/disables the joystick, and makes sure
 * that the button state is read correctly...
 */
void setup(void)
{
  enable_joystick_1x();
  enable_joystick_1y();
  disable_joystick_2x();
  disable_joystick_2y();
  joy_digital();
  read_buttons();                     /* read it twice, I had trouble doing it once only :-( */
  wait_recal();                       /* one round */
  read_buttons();
  wait_recal();                       /* one round */
}

/*
 * Our main function we start of here...
 * we should make sure that we never return from here, or vectrex will
 * be surely bothered!
 */
int main(void)
{
  unsigned char anim_state;           /* our animation state counter */
  signed char pacman_x;               /* where is the pacman? */
  signed char pacman_y;
  pacman_x = 0;
  pacman_y = 0;
  anim_state = 0;
  setup();                            /* setup our program */

  while (true)                        /* never to return... */
  {
    start_one_vectrex_round();        /* start 'de round */
    intensity(MAX_BRIGHTNESS);        /* set some brightness */
    set_scale(MOVE_SCALE);            /* set scale factor */
    print_str(-128,100, "JOYTICK 1 TO MOVE PACMAN!"); /* a message! */
    move_to(pacman_x, pacman_y);      /* position pacman */
    set_scale(PACMAN_SCALE);          /* set scale factor for the sprite */
    draw_vector_list(pacman[anim_state]); /* draw the current pacman */
    anim_state++;                     /* next time the next animation */
    if (anim_state == MAX_ANIM)       /* could do a % MAXANIM, but this is */
       anim_state = 0;                /* more optimized */
    if (!read_ram(Vec_Music_Flag))    /* music finished? */
       play_song(SCRAMBLE_MUSIC);     /* if so ... restart */
    if (joystick1_x>0)                /* check the joystick and */
    {                                 /* update position */
      pacman_x++;
    }
    else if (joystick1_x<0)
    {
      pacman_x--;
    }
    if (joystick1_y>0)
    {
      pacman_y++;
    }
    else if (joystick1_y<0)
    {
      pacman_y--;
    }
    if (pacman_x>=100) pacman_x = 100;    /* make sure pacman is not */
    if (pacman_x<=-100) pacman_x = -100;  /* out of bounds */
    if (pacman_y>=100) pacman_y = 100;
    if (pacman_y<=-100) pacman_y = -100;
    joy_digital();                        /* call once per round, to insure */
  } /* while (true) */                    /* joystick information is up to date */
}

/* END OF FILE */
