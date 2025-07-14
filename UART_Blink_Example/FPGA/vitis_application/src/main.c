#include "xuartps.h"
#include "xparameters.h"
#include "xil_printf.h"

#define UART0_ADDR 0xe0000000 // UART0 Vitis
#define UART1_ADDR 0xe0001000 // UART1 STM32

XUartPs uart0;
XUartPs uart1;

void uart_init(XUartPs *uart, u32 BaseAddress) {
    XUartPs_Config *config = XUartPs_LookupConfig(BaseAddress);
    if (!config) {
        xil_printf("UART%d config lookup failed!\n", BaseAddress);
        return;
    }

    int status = XUartPs_CfgInitialize(uart, config, config->BaseAddress);
    if (status != XST_SUCCESS) {
        xil_printf("UART%d init failed!\n", BaseAddress);
        return;
    }

    XUartPs_SetBaudRate(uart, 115200);
}

void uart_tx(XUartPs *uart, const u8 *msg) {
    XUartPs_Send(uart, msg, strlen((char *)msg));
}

int main() {
    
    uart_init(&uart0, UART0_ADDR);
    xil_printf("UART 0 initialized\n"); 
    uart_init(&uart1, UART1_ADDR);
    xil_printf("UART 1 initialized\n");  


    xil_printf("Starting STM32 PMOD Uart Test\n");

    // Debug
    //XUartPs_SendByte(STDOUT_BASEADDRESS, 'A');


    const u8 msg[] = "Hello STM32!\r\n";

    while (1) {
        uart_tx(&uart0, msg);  // Message to uart0 or stdout
        uart_tx(&uart1, msg);  // Message to STM32

        for (volatile int i = 0; i < 10000000; i++);
    }

    return 0;
}