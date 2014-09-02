#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>

#include "vectrex.h"
#include "pecado.h"
#include "menu.h"

static uint8_t i = 0;
static uint8_t state = 0;
static uint8_t frame;
                             
void SelectROM(uint8_t index) {
    memcpy((void *)0xc800, Ram_Dummy, 128);
    ((RAMFUNC)((void *)0xc800))(index);

    //NMI_VEC = ROM_ENTRY_POINT;
    //ROM_SELECTOR = index;

    //((ROMENTRY)((void *)0xf000))();
    for(;;);
}

int main()
{
    FRAMEFUNC frame_func = MainFrame;
    MainFrameInit();

    enable_joystick_1x();
    enable_joystick_1y();

    frame_func = Start_Anim;

    Set_Refresh(0x927c);

    uint8_t anal_precision = 0x08; 
    uint8_t butt_on = 0;

    for (frame = 0;; frame++) {
        butt_on = Read_Btns();

        // wait for frame boundary (one frame = 30,000 cyles = 50 Hz)
        Wait_Recal();

        switch (state = frame_func(frame, butt_on)) {
        case 1: frame_func = MainFrame;
                break;
        case 2: frame = 0;
                frame_func = SelectedFrame;
                break;
        case 3: SelectROM(GetSelectedROMIndex());
                break;
        default:
                break;
        }
        // zero the integrators and set active ground
        //Reset0Ref();

        // Joy_Digital is faster and less noisy than analog
        Joy_Digital();

        //if (butt_on)
        //  anal_precision = butt_on << 1;
        //if (anal_precision == 0x10) {
        //  Joy_Digital();
        //} else {
        //  Joy_Analog(anal_precision);
        //}

    }
    return 0;
}
