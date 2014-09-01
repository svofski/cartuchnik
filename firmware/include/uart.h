#pragma once

#include "LPC17xx.h"

#define PCUART0_POWERON (1 << 3)
#define PCUART1_POWERON (1 << 4)
#define PCUART2_POWERON (1 << 24)
#define PCUART3_POWERON (1 << 25)

#define PCLK_UART0_MASK (3 << 6)    // PCLKSEL0
#define PCLK_UART1_MASK (3 << 8)    // PCLKSEL0
#define PCLK_UART2_MASK (3 << 16)   // PCLKSEL1
#define PCLK_UART3_MASK (3 << 18)   // PCLKSEL1
#define PCLK_UART0_SHIFT 6
#define PCLK_UART1_SHIFT 8
#define PCLK_UART2_SHIFT 16
#define PCLK_UART3_SHIFT 18

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80


#define RX_BUFFER_SIZE 8

class IRQAware {
public:
    virtual void IRQHandler(void) {}
};

IRQAware* (UART_Handlers[4]);

template <class LPC_UART_T>
    class UART : public IRQAware
{
private:
    LPC_UART_T* LPC_UART;
    int m_UartNo;
    int m_Initialized;

    uint8_t rx_buffer[RX_BUFFER_SIZE];
    volatile int rx_buffer_in;
    volatile int rx_buffer_out;


public:
    UART(LPC_UART_T* uart_struct, int uartNo) {
        LPC_UART = uart_struct;
        m_UartNo = uartNo;
        UART_Handlers[uartNo] = this;
        m_Initialized = 0;
    }

    void Init(int baudrate)
    {
        int pclk;
        unsigned long int Fdiv;

        // PCLK_UART0 is being set to 1/4 of SystemCoreClock
        pclk = SystemCoreClock / 4;	

        // turn on power to UART and select peripheral clock
        // PCLK_periph = CCLK/4
        switch (m_UartNo) {
            case 0:
                LPC_SC->PCONP |= PCUART0_POWERON;
                LPC_SC->PCLKSEL0 &= ~(PCLK_UART0_MASK);
                LPC_SC->PCLKSEL0 |= (0 << PCLK_UART0_SHIFT);		
                break;
            case 1:
                LPC_SC->PCONP |= PCUART1_POWERON;
                LPC_SC->PCLKSEL0 &= ~(PCLK_UART1_MASK);
                LPC_SC->PCLKSEL0 |= (0 << PCLK_UART1_SHIFT);		
                break;
            case 2:
                LPC_SC->PCONP |= PCUART2_POWERON;
                LPC_SC->PCLKSEL1 &= ~(PCLK_UART2_MASK);
                LPC_SC->PCLKSEL1 |= (0 << PCLK_UART2_SHIFT);		
                break;
            case 3:
                LPC_SC->PCONP |= PCUART3_POWERON;
                LPC_SC->PCLKSEL1 &= ~(PCLK_UART3_MASK);
                LPC_SC->PCLKSEL1 |= (0 << PCLK_UART3_SHIFT);		
                break;
        }

        // configure I/O pins
        switch (m_UartNo) {
            case 0:
                LPC_PINCON->PINSEL0 &= ~0xf0;           // bits 8,7,6,5 = 0101
                LPC_PINCON->PINSEL0 |= ((1<<4) | (1<<6));
                break;
            case 1:
                LPC_PINCON->PINSEL0 &= ~0xc0000000;     // bits 31,30 = 01 TXD1
                LPC_PINCON->PINSEL0 |= 0x40000000; 
                LPC_PINCON->PINSEL1 &= ~3;              // bits 1,0 = 01 RXD1
                LPC_PINCON->PINSEL1 |= 2;
                break;
            case 2:
                LPC_PINCON->PINSEL0 &= ~(0xf << 20);    // bits 23,22,21,20 = 0101
                LPC_PINCON->PINSEL0 |= 5 << 20;
                break;
            case 3:
                LPC_PINCON->PINSEL0 &= ~0xf;            // bits 4,3,2,1 = 1010
                LPC_PINCON->PINSEL0 |= 0xa;
                break;
        }

        LPC_UART->LCR = 0x83;		        // 8 bits, no Parity, 1 Stop bit, DLAB=1
        Fdiv = ( pclk / 16 ) / baudrate;	// Set baud rate
        LPC_UART->DLM = Fdiv / 256;
        LPC_UART->DLL = Fdiv % 256;
        /* 0x07 == 2 stop bits */
        LPC_UART->LCR = 0x03;		        // 8 bits, no Parity, 1 Stop bit DLAB = 0
        LPC_UART->FCR = 0x07;		        // Enable and reset TX and RX FIFO

        rx_buffer_in = rx_buffer_out = 0;

        // Enable receive interrupt
        LPC_UART->IER = IER_RBR;

        m_Initialized = 0 == 0;
    }

    void UnInit(void) {
        // Disable receive interrupt
        LPC_UART->IER = 0;

        // turn off power to UART and select peripheral clock
        // PCLK_periph = CCLK/4
        switch (m_UartNo) {
            case 0:
                LPC_SC->PCONP &= ~PCUART0_POWERON;
                break;
            case 1:
                LPC_SC->PCONP &= ~PCUART1_POWERON;
                break;
            case 2:
                LPC_SC->PCONP &= ~PCUART2_POWERON;
                break;
            case 3:
                LPC_SC->PCONP &= ~PCUART3_POWERON;
                break;
        }

        m_Initialized = 0;
    }

    void Sendchar(char c)
    {
        if (m_Initialized) {
            while( (LPC_UART->LSR & LSR_THRE) == 0 );	// Block until tx empty

            LPC_UART->THR = c;
        }
    }

    char Getchar()
    {
        if (m_Initialized) {
            while(!Avail());
            return Getc();
        }
    }

    uint8_t Getc() 
    {
        uint8_t result = rx_buffer[rx_buffer_out];
        rx_buffer_out = (rx_buffer_out + 1) % RX_BUFFER_SIZE;
        return result;
    }

    int Avail() 
    {
        return rx_buffer_in != rx_buffer_out;
    }

    void IRQHandler (void)
    {
        rx_buffer[rx_buffer_in] = (uint8_t)LPC_UART->RBR; // this must clear interrupt flag
        rx_buffer_in = (rx_buffer_in + 1) % RX_BUFFER_SIZE;
    }
};

extern "C" {
void UART0_IRQHandler (void)
{
    UART_Handlers[0]->IRQHandler();
}
}
/* vim: set et sw=4: */
