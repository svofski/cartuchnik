#pragma once

void Moveto(uint8_t x, uint8_t y);
void Set_Refresh(uint16_t value);
void Wait_Recal(void);
void Reset0Ref(void);
void Intensity(uint8_t i);
void Draw_VLp_7f(uint8_t* path, uint8_t zeroskip);
void Draw_VLp_b(uint8_t* path, uint8_t scale, uint8_t zeroskip);
void Draw_VLp_scale(uint8_t* path, uint8_t zeroskip);
void Print_Str_d(int8_t x, int8_t y, const char *str);

/* ... */
#define enable_joystick_1x() __asm__ ("lda \t#1 \t; enable\n\tsta \t0HC81F \t; Vec_Joy_Mux_1_X":::"a")
/* ... */
#define disable_joystick_1x() __asm__ ("lda \t#0 \t; disable\n\tsta \t0HC81F \t; Vec_Joy_Mux_1_X":::"a")
/* ... */
#define enable_joystick_1y() __asm__ ("lda \t#3 \t; enable\n\tsta \t0HC820 \t; Vec_Joy_Mux_1_Y":::"a")
/* ... */
#define disable_joystick_1y() __asm__ ("lda \t#0 \t; disable\n\tsta \t0HC820 \t; Vec_Joy_Mux_1_Y":::"a")
/* ... */
#define enable_joystick_2x() __asm__ ("lda \t#5 \t; enable\n\tsta \t0HC821 \t; Vec_Joy_Mux_2_X":::"a")
/* ... */
#define disable_joystick_2x() __asm__ ("lda \t#0 \t; disable\n\tsta \t0HC821 \t; Vec_Joy_Mux_2_X":::"a")
/* ... */
#define enable_joystick_2y() __asm__ ("lda \t#7 \t; enable\n\tsta \t0HC822 \t; Vec_Joy_Mux_2_Y":::"a")
/* ... */
#define disable_joystick_2y() __asm__ ("lda \t#0 \t; disable\n\tsta \t0HC822 \t; Vec_Joy_Mux_2_Y":::"a")

#define joystick1_x (* ((int8_t *) 0xc81b))
#define joystick1_y (* ((int8_t *) 0xc81c))
#define joystick2_x (* (int8_t *) 0xc81d)
#define joystick2_y (* (int8_t *) 0xc81e)

void Joy_Digital(void);
void Joy_Analog(uint8_t precision);

#define JOY1_BUTTON1	0x01
#define JOY1_BUTTON2 	0x02
#define JOY1_BUTTON3	0x04
#define JOY1_BUTTON4	0x08
#define JOY2_BUTTON1	0x10
#define JOY2_BUTTON2 	0x20
#define JOY2_BUTTON3	0x40
#define JOY2_BUTTON4	0x80

uint8_t Read_Btns(void);

#define ROM_SELECTOR	(* ((int8_t *) 0x0000))

#define NMI_VEC	(* ((int16_t *) 0xcbfb))
#define SWI_VEC	(* ((int16_t *) 0xcbfb))
#define IRQ_VEC	(* ((int16_t *) 0xcbf8))
#define FIRQ_VEC (* ((int16_t *) 0xcbf5))
#define ROM_ENTRY_POINT 0xF000

typedef int (*FRAMEFUNC)(int, uint8_t);

typedef void (*ROMENTRY)(void);

typedef void (*RAMFUNC)(uint8_t);

void Ram_Dummy(uint8_t index);
