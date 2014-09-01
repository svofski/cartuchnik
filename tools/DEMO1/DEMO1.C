/*
 * Include some standard vectrex functions first!
 */
#include <vectrex.h>


/*
 * Some defines, Maximal brightness is $7f, highest not set!
 * Max Scale would be $ff, well here we take only $f0!
 */
#define MAX_BRIGHTNESS (0x7f)

/*
 * Our main function we start of here...
 * we should make sure that we never return from here, or vectrex will
 * be surely bothered!
 */
int main(void)
{
  while (true)                                  /* never to return... */
  {
    wait_recal();                               /* recalibrate vectrex */
    intensity(MAX_BRIGHTNESS);                  /* set some brightness */
    print_str(-70,0,"HELLO WORLD!");            /* print hello world! */
  } /* while (true) */
}

/* END OF FILE */
