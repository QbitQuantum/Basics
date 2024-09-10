DWORD 
HW_Read(
    PI2C_CONTEXT pI2C,
    DWORD  SlaveAddr,   // slave address
    UCHAR  WordAddr,    // starting word address
    PUCHAR pData,       // pdata
    DWORD  Count        // bytes to read
    )
{
    DWORD  dwErr;

    if ( !VALID_CONTEXT(pI2C) )
        return ERROR_INVALID_PARAMETER;
        
    DEBUGMSG(ZONE_READ|ZONE_TRACE,(TEXT("+I2C_Read[%u]: 0x%X, 0x%X, 0x%X, %u\r\n"), 
        pI2C->State, SlaveAddr, WordAddr, pData, Count));
    
    if ( !pData || !Count || IsBadWritePtr(pData, Count) ) {
        DEBUGMSG(ZONE_ERR,(TEXT("I2C_Read ERROR: invalid parameter \r\n")));
        return ERROR_INVALID_PARAMETER;
    }

    EnterCriticalSection(&pI2C->RegCS);
    
    if ( pI2C->State != IDLE) {
        DEBUGMSG(ZONE_ERR,(TEXT("I2C_Read ERROR: i2cState: %u \r\n"), pI2C->State));
        LeaveCriticalSection(&pI2C->RegCS);
        return ERROR_BUSY;
    }

    pI2C->LastError = ERROR_SUCCESS;
    
    ResetEvent(pI2C->DoneEvent);

    rIICSTAT = M_ACTIVE;
    
    // pre-setup word address
    pI2C->Data = NULL;
    pI2C->State = SET_READ_ADDR;
    pI2C->WordAddr = WordAddr;
    pI2C->Flags.WordAddr = TRUE;
    pI2C->DataCount = 1;
    
    // enable the slave address drop
    pI2C->Flags.DropRxAddr = TRUE;

    // write slave address
    rIICDS = (UCHAR)SlaveAddr;
    rIICSTAT = MTX_START;

    // Wait for IST to write the word address
    if (WAIT_OBJECT_0 != SyncIst(pI2C, RX_TIMEOUT)) {
        
        DEBUGMSG(ZONE_READ|ZONE_ERR,(TEXT("RX_TIMEOUT.1\r\n")));

        goto _done;
    }

    ResetEvent(pI2C->DoneEvent);

    // get read data
    pI2C->State = READ_DATA;
    pI2C->Data = pData;
    pI2C->DataCount = Count;
    rIICDS = (UCHAR)SlaveAddr;
    rIICSTAT = MRX_START;
    rIICCON  = RESUME_ACK;  // Resume IIC operation (clear bit 4)

    // Wait for IST to get data
    if (WAIT_OBJECT_0 != SyncIst(pI2C, RX_TIMEOUT)) {
        
        DEBUGMSG(ZONE_READ|ZONE_ERR,(TEXT("RX_TIMEOUT.2\r\n")));

        goto _done;
    }



_done:    
    rIICSTAT  = M_IDLE;    // disable Rx/Tx
    pI2C->State = IDLE;
    pI2C->Data  = NULL;
    pI2C->DataCount = INVALID_DATA_COUNT;

    if ( !pI2C->LastError && (SlaveAddr != pI2C->RxRetAddr) ) {

        DEBUGMSG(ZONE_READ|ZONE_ERR,(TEXT("I2C_Read Invalid Return Address: 0x%X != 0x%X \r\n"), 
            pI2C->RxRetAddr, SlaveAddr ));

        pI2C->LastError = ERROR_INCORRECT_ADDRESS;

        TEST_TRAP;
    }
    
    pI2C->RxRetAddr = 0;

    dwErr = pI2C->LastError;
    
    LeaveCriticalSection(&pI2C->RegCS);
    
    DEBUGMSG(ZONE_READ|ZONE_TRACE,(TEXT("-I2C_Read:%u \r\n"), dwErr ));
	//RETAILMSG(1,(_T("data = 0x%X\r\n", *pData)));

    return dwErr;
}