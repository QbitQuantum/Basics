/******************************************************************************
 *
 *  Name: MrvDrvCheckForHang()
 *
 *  Description:
 *      NDIS miniport check for hang routine.
 *
 *  Conditions for Use:
 *      Will be called by NDIS wrapper to determine current station operation status.
 *      If the station is not responding, NDIS wrapper will call MrvDrvReset() to reset
 *      the station. Driver first check and use current HW status stored in device
 *      object to report system then update the status and send command to query HW status.
 *
 *  Arguments:
 *      IN NDIS_HANDLE MiniportAdapterContext
 *
 *  Return Value:
 *    TRUE if the NIC HW is not operating properly
 *    FALSE if the NIC HW is OK
 *
 *  Notes: According to Microsoft NDIS document, this function is normally called
 *         by NDIS wrapper approximately every 2 seconds.
 *
 *****************************************************************************/
BOOLEAN
MrvDrvCheckForHang(
    IN NDIS_HANDLE MiniportAdapterContext
)
{
    PMRVDRV_ADAPTER  Adapter;

    UCHAR            ucHostIntStatus;
    UCHAR            ucCardStatus;
    SD_API_STATUS    status;

    DBGPRINT(DBG_LOAD|DBG_WARNING,(L"INIT - Enter MrvDrvCheckForHang\n"));
    //return FALSE; //tt ra fail

    Adapter = (PMRVDRV_ADAPTER)MiniportAdapterContext;

    if ( Adapter->SurpriseRemoved )
    {
        DBGPRINT(DBG_WARNING, (L"[MRVL] in CheckForHang, card is removed, return FALSE directly\n") );
        return FALSE;
    }


    if ( Adapter->SentPacket )
    {
        Adapter->dwTxTimeoutCount ++;
        if ( Adapter->dwTxTimeoutCount > MRVDRV_TX_TIMEOUT_COUNT_THRESHOLD )
        {
            DBGPRINT( DBG_ERROR, (L"Tx timeout!\n") );
            Adapter->TxPktTimerIsSet=TRUE;
            NdisMSetTimer(&Adapter->MrvDrvTxPktTimer, 0);
            Adapter->dwTxTimeoutCount = 0;
        }
    }


    //012207
    // We won't check in deepsleep, ps mode, HostSleep and D3 state.
    // In Deep Sleep Mode no packet can be sent out
    if( !IsThisDsState(Adapter, DS_STATE_NONE) )
        return FALSE;

    if( (!IsThisHostPowerState(Adapter, HTWK_STATE_FULL_POWER)) ||
            (Adapter->psState == PS_STATE_SLEEP) ||
            (Adapter->CurPowerState != NdisDeviceStateD0)
      )
        return FALSE;
    if ( Adapter->IntWARTimeoutCount )
        AutoDeepSleepCounter(Adapter);
    else
        Adapter->AutoDsRec.timer = 0;

    //060407 flag to start auto deep sleep counter
    //This flag also used to interrupt missing.
    if(((++Adapter->IntWARTimeoutCount) & 0x1) == 0 )
        return FALSE;

    //Adapter->IntWARTimeoutCount = 0;

    if( IsThisDsState(Adapter, DS_STATE_SLEEP) )
        return FALSE;

    status = If_ReadRegister(Adapter,
                             //SD_IO_READ ,
                             1, // function 1
                             HCR_HOST_INT_STATUS_REGISTER,
                             FALSE,
                             &ucHostIntStatus,
                             sizeof(ucHostIntStatus));

    if (!SD_API_SUCCESS(status))
    {
        DBGPRINT(DBG_ERROR, (L"Read error in CheckForHang()\r\n") );
        return FALSE;
    }

    if( ucHostIntStatus & (UPLOAD_HOST_INT_STATUS_RDY | DOWNLOAD_HOST_INT_STATUS_RDY) )
    {

        EnterCriticalSection(&Adapter->IntCriticalSection);
        Adapter->ucGHostIntStatus |= ucHostIntStatus;
        LeaveCriticalSection(&Adapter->IntCriticalSection);
        ucCardStatus = ~ucHostIntStatus;
        ucCardStatus &= 0x1f;
        status = If_WriteRegister(Adapter,
                                  //SD_IO_WRITE,
                                  1,
                                  HCR_HOST_INT_STATUS_REGISTER,
                                  FALSE,
                                  &ucCardStatus,   // reg
                                  sizeof(ucCardStatus));

        if (!SD_API_SUCCESS(status))
        {
            DBGPRINT(DBG_ISR,(L"Unable to clear Host interrupt status register\r\n"));
            return FALSE;
        }

        SetEvent(Adapter->hControllerInterruptEvent);
    }



    return FALSE;

}