#include "uart.h"

UART<LPC_UART_TypeDef> uart0(LPC_UART0, 0);

extern "C" {
int xputchar(int ch) {
    if (ch == '\n')
        uart0.Sendchar('\r');
    uart0.Sendchar(ch);
    return 0;
}

void UART0_Init(int baudrate) {
    uart0.Init(baudrate);
}

void UART0_UnInit() {
	uart0.UnInit();
}

}