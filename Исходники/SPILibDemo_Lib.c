int WINAPI WinMain(HINSTANCE hInstance,      // handle to current instance
                   HINSTANCE hPrevInstance,  // handle to previous instance
                   LPWSTR lpCmdLine,          // pointer to command line
                   int nCmdShow)             // show state of window
{

    HANDLE tRx, tTx;
    BOOL dma_enable = FALSE;

    NKDbgPrintfW(L"******************************************\n\r");
    NKDbgPrintfW(L"*********    Program Start  **************\n\r");
    NKDbgPrintfW(L"******************************************\n\r");

    dma_enable = FALSE;

    bufferTx = sbufferTx;
    bufferRx = sbufferRx;

    if ((bufferRx == NULL) || (bufferTx == NULL))
    {
        printf("Could not alloc buffers");
        return FALSE;
    }

    //Initialize SSP1 (Master)
    //-----------------------------
    if (!SPIInit(txSSPport, DATABITS, SPI_CLOCK_812_KHZ, SPI_MASTER, SPI_MODE_3, NULL))
    {
        printf("Error in InitSPI");
        return FALSE;
    }

    //Initialize SSP2 (Slave)
    //-----------------------------
    if (!SPIInit(rxSSPport, DATABITS, SPI_CLOCK_812_KHZ, SPI_SLAVE, SPI_MODE_3, NULL))
    {
        printf("Error in InitSPI");
        return FALSE;
    }

    //Create and start transmit/receive threads
    //-----------------------------
    tRx = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) RXThread, 0, 0, NULL);
    CeSetThreadPriority(tRx,10);  //Set receive thread to a high priority to avoid buffer overflows

    //Sleep(100);
    tTx = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) TXThread, 0, 0, NULL);

    printf("\r\nPress ENTER to leave the application.\r\n");
    getchar();

    TerminateThread(tRx, 0);
    TerminateThread(tTx, 0);
    Sleep(20);

    CloseHandle(tRx);
    CloseHandle(tTx);

    //Deinit
    //Very Important
    //if you forget to Deinit a SPI and Init the SPI new the spi interrupts will not work.
    //In this case you have to reset the System
    DeinitSPI(txSSPport);
    DeinitSPI(rxSSPport);

    return TRUE;

}