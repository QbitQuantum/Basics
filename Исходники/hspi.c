PSPI_PUBLIC_CONTEXT HSP_Init(PVOID Context) 
{
	LPTSTR          				ActivePath = (LPTSTR) Context; // HKLM\Drivers\Active\xx
	PSPI_PUBLIC_CONTEXT		pPublicSpi = NULL;
	BOOL            				bResult = TRUE;
	DWORD           			dwHwIntr=0;

	RETAILMSG(1,(TEXT("++HSP_Init Function\r\n")));
	RETAILMSG(1,(TEXT("Active Path : %s\n"), ActivePath));

	if ( !(pPublicSpi = (PSPI_PUBLIC_CONTEXT)LocalAlloc( LPTR, sizeof(SPI_PUBLIC_CONTEXT) )) )
	{
		RETAILMSG(1,(TEXT("Can't not allocate for SPI Context\n")));
		return NULL;
	}


    if(!HW_Init(pPublicSpi)) 
    {
    	RETAILMSG(1,(TEXT("HW_Init is failed\n")));
    	return NULL;
    } else {
    	RETAILMSG(1,(TEXT("HW_Init is completed\n")));
    }
    
	do 
	{
		InitializeCriticalSection(&(pPublicSpi->CsRxAccess));
		InitializeCriticalSection(&(pPublicSpi->CsTxAccess));

		//Rx Thread
		pPublicSpi->hRxEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		
		pPublicSpi->hRxThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadForRx, (LPVOID)pPublicSpi, 0, (LPDWORD)&pPublicSpi->dwRxThreadId);
		if (pPublicSpi->hRxThread == NULL)
		{
			RETAILMSG(1,(TEXT("SPI Rx Thread creation error!!!\n")));
			bResult = FALSE;
			break;
		}
		
		pPublicSpi->hRxDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);		
		pPublicSpi->hRxIntrDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		
		//Tx Thread
		pPublicSpi->hTxEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		
		pPublicSpi->hTxThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadForTx, (LPVOID)pPublicSpi, 0, (LPDWORD)&pPublicSpi->dwTxThreadId);
		if (pPublicSpi->hTxThread == NULL)
		{
			RETAILMSG(1,(TEXT("SPI Dma Thread creation error!!!\n")));
			bResult = FALSE;
			break;
		}
		
		pPublicSpi->hTxDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);		
		pPublicSpi->hTxIntrDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		
		//Spi ISR
		pPublicSpi->dwSpiSysIntr = SYSINTR_NOP;
		dwHwIntr = IRQ_SPI1;		//HS-SPI

		pPublicSpi->hSpiEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		
		if (!KernelIoControl(IOCTL_HAL_REQUEST_SYSINTR, &dwHwIntr, sizeof(DWORD), &pPublicSpi->dwSpiSysIntr, sizeof(DWORD), NULL))
		{
			RETAILMSG(1,(TEXT("Failed to request the SPI sysintr.\n")));
			pPublicSpi->dwSpiSysIntr = SYSINTR_UNDEFINED;
			bResult = FALSE;
			break;
		}

		if (!InterruptInitialize(pPublicSpi->dwSpiSysIntr, pPublicSpi->hSpiEvent, NULL, 0))
		{
			RETAILMSG(1,(TEXT("SPI Interrupt Initialization failed!!!\n")));
			bResult = FALSE;
			break;
		}

		pPublicSpi->hSpiThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadForSpi, (LPVOID)pPublicSpi, 0, (LPDWORD)&pPublicSpi->dwSpiThreadId);
		if (pPublicSpi->hSpiThread == NULL)
		{
			RETAILMSG(1,(TEXT("SPI ISR Thread creation error!!!\n")));
			bResult = FALSE;
			break;
		}
		
		
		//Rx DMA Done ISR
		pPublicSpi->dwRxDmaDoneSysIntr = SYSINTR_NOP;	
		dwHwIntr = IRQ_DMA3;	

		pPublicSpi->hRxDmaDoneDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		pPublicSpi->hRxDmaDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);


		if (!KernelIoControl(IOCTL_HAL_REQUEST_SYSINTR, &dwHwIntr, sizeof(DWORD), &pPublicSpi->dwRxDmaDoneSysIntr, sizeof(DWORD), NULL))
		{
			RETAILMSG(1,(TEXT("Failed to request the SPI_DMA sysintr.\n")));
			pPublicSpi->dwRxDmaDoneSysIntr = SYSINTR_UNDEFINED;
			bResult = FALSE;
			break;
		}

		if (!InterruptInitialize(pPublicSpi->dwRxDmaDoneSysIntr, pPublicSpi->hRxDmaDoneEvent, NULL, 0))
		{
			RETAILMSG(1,(TEXT("DMA Interrupt Initialization failed!!!\n")));
			bResult = FALSE;
			break;
		}

		pPublicSpi->hRxDmaDoneThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadForRxDmaDone, (LPVOID)pPublicSpi, 0, (LPDWORD)&pPublicSpi->dwRxDmaDoneThreadId);
		if (pPublicSpi->hRxDmaDoneThread == NULL)
		{
			RETAILMSG(1,(TEXT("SPI Dma Thread creation error!!!\n")));
			bResult = FALSE;
			break;
		}
		
		//Tx DMA Done ISR
		pPublicSpi->dwTxDmaDoneSysIntr = SYSINTR_NOP;
		dwHwIntr = IRQ_DMA4;		
		
		pPublicSpi->hTxDmaDoneDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		pPublicSpi->hTxDmaDoneEvent = CreateEvent(NULL, FALSE, FALSE, NULL);


		if (!KernelIoControl(IOCTL_HAL_REQUEST_SYSINTR, &dwHwIntr, sizeof(DWORD), &pPublicSpi->dwTxDmaDoneSysIntr, sizeof(DWORD), NULL))
		{
			RETAILMSG(1,(TEXT("Failed to request the SPI_DMA sysintr.\n")));
			pPublicSpi->dwTxDmaDoneSysIntr = SYSINTR_UNDEFINED;
			bResult = FALSE;
			break;
		}

		if (!InterruptInitialize(pPublicSpi->dwTxDmaDoneSysIntr, pPublicSpi->hTxDmaDoneEvent, NULL, 0))
		{
			RETAILMSG(1,(TEXT("DMA Interrupt Initialization failed!!!\n")));
			bResult = FALSE;
			break;
		}

		pPublicSpi->hTxDmaDoneThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadForTxDmaDone, (LPVOID)pPublicSpi, 0, (LPDWORD)&pPublicSpi->dwTxDmaDoneThreadId);
		if (pPublicSpi->hTxDmaDoneThread == NULL)
		{
			RETAILMSG(1,(TEXT("SPI Dma Thread creation error!!!\n")));
			bResult = FALSE;
			break;
		}
	} while (0);
	
	
	if(bResult) return pPublicSpi;
	else 		return NULL;
}