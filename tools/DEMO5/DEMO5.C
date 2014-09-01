/*
 * Include some standard vectrex functions first!
 */
#include <vectrex.h>

/* NON CONSTANT VARIABLES NOT ALLOWED TO BE INITIALIZED */

/*
 * Some defines, Maximal brightness is $7f, highest not set!
 * Max Scale would be $ff, well here we take only $f0!
 */
#define MAX_BRIGHTNESS (0x7f)

/*
 * Nicer would have been an enum... what the heck... 8 possible directions
 * THREE e.g. mean from left to right...
 */
#define TO_HALF_THREE 0
#define TO_THREE 1
#define TO_HALF_SIX 2
#define TO_SIX 3
#define TO_HALF_NINE 4
#define TO_NINE 5
#define TO_HALF_TWELF 6
#define TO_TWELF 7
#define HIGHEST_DIRECTION (TO_TWELF + 1)

/*
 * Define some constants that determine the output
 */
#define HIGHEST_SPEED 4                 /* highest speed of the dots */
#define SHOT_SCALE 120                  /* for positioning the dots on the screen */
#define SHOTS 50                        /* how many dots at one time? */
#define DOT_BRIGHTNESS 5                /* dot dwell time... */
#define SHOT_INTERVALL 2                /* how much time between reapearing at a */
                                        /* new location? */

struct shot                             /* one shot... */
{
  signed short shot_counter;            /* time keeper, when should it appear?*/
  signed char direction;                /* ... */
  unsigned char speed;
  unsigned char hunting;                /* not used */
  signed x;
  signed y;
};

struct shot current_shots[SHOTS];       /* all dots bundled */

/*
 * Inlined static... insures this is 'really' inlined completely...
 *
 * This function sets up a random shop, going in one of eight
 * possible directions from one end of the screen to another...
 *
 */
static inline void init_shot(struct shot *current_shot)
{
  unsigned char choice = random() % 4;          /* start on which side? */
  unsigned char start = random();               /* start on which position? */
  current_shot->shot_counter = -1;              /* shotcounter negative -> active */
  current_shot->direction = random() % HIGHEST_DIRECTION; /* random direction of shot */
  current_shot->speed = (random() & 3) + 1;     /* random speed */
  current_shot->hunting = 0;                    /* still not used :-) */
  if (choice == 0)                              /* do the starting */
  {                                             /* coordinates... */
    current_shot->y = -127;
    current_shot->x = start;
  }
  if (choice == 1)
  {
    current_shot->y = 127;
    current_shot->x = start;
  }
  if (choice == 2)
  {
    current_shot->y = start;
    current_shot->x = -127;
  }
  if (choice == 3)
  {
    current_shot->y = start;
    current_shot->x = 127;
  }
}

/*
 * Inlined static... insures this is 'really' inlined completely...
 *
 * Process one dot...
 *
 */
static inline void do_shot(struct shot *current_shot)
{
  zero_beam();                          /* reset beam to middle of screen */
  if (current_shot->shot_counter > 0)   /* is this shot active? */
  {
    current_shot->shot_counter--;       /* no?, than reduce counter... */
    if (current_shot->shot_counter == 0) /* if 0... make active and set up */
    {
      init_shot(current_shot);
    }
    return;                             /* next time shot will be active, */
  }                                     /* for now... return */
  else
  {
    switch (current_shot->direction)    /* process direction flag */
    {
     case TO_HALF_THREE:
     {
       /* is dot out of bounds? */
       if ((current_shot->x > 120) || (current_shot->y > 120) )
       {
         /* yep, than make inactive and reset 'timer' */
         current_shot->shot_counter = SHOT_INTERVALL;
         /* and bye */
         return;
       }
       current_shot->x += current_shot->speed;
       current_shot->y += current_shot->speed;
       break;
     }
     case TO_THREE:
     {
       /* is dot out of bounds? */
       if (current_shot->x > 120)
       {
         /* yep, than make inactive and reset 'timer' */
         current_shot->shot_counter = SHOT_INTERVALL;
         /* and bye */
         return;
       }
       /* otherwise process coordinated according to direction and speed */
       current_shot->x += current_shot->speed;
       break;
     }
     case TO_HALF_SIX:
     {
       /* is dot out of bounds? */
       if ((current_shot->x > 120) || (current_shot->y < -120) )
       {
         /* yep, than make inactive and reset 'timer' */
         current_shot->shot_counter = SHOT_INTERVALL;
         /* and bye */
         return;
       }
       /* otherwise process coordinated according to direction and speed */
       current_shot->x += current_shot->speed;
       current_shot->y -= current_shot->speed;
       break;
     }
     case TO_SIX:
     {
       /* is dot out of bounds? */
       if (current_shot->y < -120)
       {
         /* yep, than make inactive and reset 'timer' */
         current_shot->shot_counter = SHOT_INTERVALL;
         /* and bye */
         return;
       }
       /* otherwise process coordinated according to direction and speed */
       current_shot->y -= current_shot->speed;
       break;
     }
     case TO_HALF_NINE:
     {
       /* is dot out of bounds? */
       if ((current_shot->x < -120) || (current_shot->y < -120) )
       {
         /* yep, than make inactive and reset 'timer' */
         current_shot->shot_counter = SHOT_INTERVALL;
         /* and bye */
         return;
       }
       /* otherwise process coordinated according to direction and speed */
       current_shot->x -= current_shot->speed;
       current_shot->y -= current_shot->speed;
       break;
     }
     case TO_NINE:
     {
       /* is dot out of bounds? */
       if (current_shot->x < -120)
       {
         /* yep, than make inactive and reset 'timer' */
         current_shot->shot_counter = SHOT_INTERVALL;
         /* and bye */
         return;
       }
       /* otherwise process coordinated according to direction and speed */
       current_shot->x -= current_shot->speed;
       break;
     }
     case TO_HALF_TWELF:
     {
       /* is dot out of bounds? */
       if ((current_shot->x < -120) || (current_shot->y > 120) )
       {
         /* yep, than make inactive and reset 'timer' */
         current_shot->shot_counter = SHOT_INTERVALL;
         /* and bye */
         return;
       }
       /* otherwise process coordinated according to direction and speed */
       current_shot->x -= current_shot->speed;
       current_shot->y += current_shot->speed;
       break;
     }
     case TO_TWELF:
     {
       /* is dot out of bounds? */
       if (current_shot->y > 120)
       {
         /* yep, than make inactive and reset 'timer' */
         current_shot->shot_counter = SHOT_INTERVALL;
         /* and bye */
         return;
       }
       /* otherwise process coordinated according to direction and speed */
       current_shot->y += current_shot->speed;
       break;
     }
     default:
     {
       /* oops... something wrong... make this false dot inactive ... */
       current_shot->shot_counter = SHOT_INTERVALL;
       return;
     }
   }
 }
 /* now draw the dot */
 write_ram(Vec_Dot_Dwell, DOT_BRIGHTNESS); /* first set up the dot dwell time */
 set_scale(SHOT_SCALE);                    /* set scale for positioning */
 draw_dot(current_shot->x, current_shot->y); /* position and draw the dot */
}

/*
 * Inlined static... insures this is 'really' inlined completely...
 *
 * Initialize all dots to starting defaults...
 *
 */
static inline void init_new_game(void)
{
  unsigned char i;
  for (i=0; i<SHOTS; i++)
  {
    current_shots[i].shot_counter = 10;
  }
}

/*
 * Inlined static... insures this is 'really' inlined completely...
 *
 * oops... a small one :-)
 *
 */
static inline void start_one_vectrex_round(void)
{
  wait_recal();
}

/*
 * Main ... what else to say?
 */

int main(void)
{
  unsigned char i;              /* a counter */
  init_new_game();              /* initialize dots ... */
  while (true)                  /* do forever... the following */
  {
    start_one_vectrex_round();  /* start vectrex round */
    intensity(MAX_BRIGHTNESS);  /* set intensity of vector beam... */
    for (i=0; i < SHOTS; i++)   /* and process all dots */
    {
      do_shot(&current_shots[i]); /* with this function ... */
    }
  }
}



/* END OF FILE */
