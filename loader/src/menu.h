#pragma once 

#include <inttypes.h>

int Start_Anim(int frame, uint8_t buttons);
int MainFrame(int frame, uint8_t buttons);
int SelectedFrame(int frame, uint8_t buttons);

void TestFrame(int frame, uint8_t buttons);
void MainFrameInit(void);
int GetSelectedROMIndex(void);