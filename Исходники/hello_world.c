/*!
 * @brief Main function
 */
int main (void)
{
    // RX buffers
    //! @param receiveBuff Buffer used to hold received data
    uint8_t receiveBuff;

    // Initialize standard SDK demo application pins
    hardware_init();

    // Call this function to initialize the console UART. This function
    // enables the use of STDIO functions (printf, scanf, etc.)
    dbg_uart_init();
    
    // Print the initial banner
    PRINTF("\r\nHello World!\n\n\r");

    while(1)
    {
        // Main routine that simply echoes received characters forever

        // First, get character
        receiveBuff = GETCHAR();

        // Now echo the received character
        PUTCHAR(receiveBuff);
    }
}