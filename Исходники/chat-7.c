DWORD HiloLectura(LPDWORD lpParam)
{
    DWORD dwEvtMask;

    OVERLAPPED ov = { 0 };
    ov.hEvent = CreateEvent(0, TRUE, 0, 0);

    //-- Recoge el manejador del puerto serie
    HANDLE hCommPort = (HANDLE)*lpParam;

    char szDatos[MAXCHARS + 1];

    DWORD dwErrors;

    //-- Bucle infinito de lectura
    while (TRUE)
    {
        if (!WaitCommEvent(hCommPort, &dwEvtMask, &ov)) {}

        if (!ClearCommError(hCommPort, &dwErrors, NULL)) {
            perror("ClearCommError");
            continue;
        }

        if (dwErrors & CE_FRAME) {
            printf("Frame error\n");
        }
        if (dwErrors & CE_RXPARITY) {
            printf("Parity error\n");
        }
        if (dwErrors & CE_OVERRUN) {
            printf("Overrun\n");
        }
        if (dwErrors & CE_BREAK) {
            printf("CE_BREAK\n");
        }
        if (dwErrors & CE_RXOVER) {
            printf("CE_RXOVER\n");
        }

        //-- Espera a que haya algo que leer
        if (WAIT_OBJECT_0 == WaitForSingleObject(ov.hEvent, INFINITE))
        {
            DWORD dwMask;
            if (GetCommMask(hCommPort, &dwMask))
            {
                if (dwMask & EV_TXEMPTY)
                {
                    ResetEvent(ov.hEvent);
                    continue;
                }
            }

            //-- Lee los datos del puerto serie
            if (serie_leer(hCommPort, szDatos, sizeof(szDatos)) > 0)
                printf("%s", szDatos);
            else
                printf("serie_leer returned 0");

            //-- Reinicia el estado del evento
            ResetEvent(ov.hEvent);
        }
    }

    return 0;
}