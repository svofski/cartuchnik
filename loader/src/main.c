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
                             
int main()
{
	FRAMEFUNC frame_func = MainFrame;
	MainFrameInit();

	enable_joystick_1x();
	enable_joystick_1y();

	frame_func = Start_Anim;

	Set_Refresh(0x927c);

	uint8_t anal_precision = 0x08; 
	for (frame = 0;; frame++) {
		// wait for frame boundary (one frame = 30,000 cyles = 50 Hz)
		Wait_Recal();

		state = frame_func(frame);
		if (state) {
			frame_func = MainFrame;
			//frame_func = TestFrame;
		}

		// zero the integrators and set active ground
		//Reset0Ref();

		uint8_t butt_on = Read_Btns();
		if (butt_on)
			anal_precision = butt_on << 1;
		if (anal_precision == 0x10) {
			Joy_Digital();
		} else {
			Joy_Analog(anal_precision);
		}
		//Read_Btns();
		//Joy_Digital();
	}
	return 0;
}
