/*
 * Include some standard vectrex functions first!
 */
#include <vectrex.h>

/*
 * Some defines, Maximal brightness is $7f, highest not set!
 * Max Scale would be $ff, well here we take only $f0!
 */
#define MAX_BRIGHTNESS (0x7f)
#define MAX_SCALE (0xf0)

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
 * Our main function we start of here...
 * we should make sure that we never return from here, or vectrex will
 * be surely bothered!
 */
int main(void)
{
  unsigned char last_button = 0;        /* one auto variable... remember the */
  read_buttons();                       /* last pressed button */
  while (true)                          /* never to return... */
  {
    start_one_vectrex_round();          /* start 'de round */
    set_scale(MAX_SCALE);               /* set scale factor */
    intensity(MAX_BRIGHTNESS);          /* set some brightness */
    print_str(-20,120, "MUSIC");        /* print on screen */
    print_str(-100,80, "BUTTON 1 SCRAMBLE");
    print_str(-100,40, "BUTTON 2 CRAZY COASTER");
    print_str(-100,00, "BUTTON 3 BERZERK ");
    print_str(-100,-40,"BUTTON 4 SOLAR QUEST");
    if ((joystick1_button1) && (last_button != 1)) /* check the button 1 */
    {
      play_song(SCRAMBLE_MUSIC);                   /* play a song */
      last_button = 1;                             /* and remember this button */
    } else
    if ((joystick1_button2) && (last_button != 2)) /* check the button 2 */
    {
      play_song(CRAZY_COASTER);                    /* play a song */
      last_button = 2;                             /* and remember this button */
    } else
    if ((joystick1_button3) && (last_button != 3)) /* check the button 3 */
    {
      play_song(BERZERK);                          /* play a song */
      last_button = 3;                             /* and remember this button */
    } else
    if ((joystick1_button4) && (last_button != 4)) /* check the button 4 */
    {
      play_song(SOLAR_QUEST);                      /* play a song */
      last_button = 4;                             /* and remember this button */
    }
    read_buttons();                                /* read again for next round */
  } /* while (true) */
}

/* END OF FILE */
