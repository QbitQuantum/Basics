/******************************************************************************
 *
 *  Name: MrvDrvSend()
 *
 *  Description: NDIS miniport serialized send packet routine
 *
 *  Conditions for Use: Protocol driver will call this routine to pass Tx NDIS_PACKET
 *
 *  Arguments:           
 *      IN  NDIS_HANDLE   MiniportAdapterContext
 *      IN  PPNDIS_PACKET Packet
 *      IN  UINT          Flags
 *    
 *  Return Value: NDIS_STATUS_RESOURCES or NDIS_STATUS_PENDING
 * 
 *  Notes:               
 *
 *****************************************************************************/
NDIS_STATUS
MrvDrvSend(
    IN NDIS_HANDLE MiniportAdapterContext,
    IN PNDIS_PACKET Packet,
    IN UINT Flags)
{
    PMRVDRV_ADAPTER Adapter;
    NDIS_STATUS Status;



       PNDIS_BUFFER  pBuffer;
       UINT            BufferCount;
    UINT           Length;   
    UINT           TotalPacketLength = 0;   
       PVOID           pVirtualAddr;
    PTxCtrlNode      pTxNode;
    PUCHAR            pHeader = NULL;
  

    Status = NDIS_STATUS_SUCCESS;  

    Adapter = (PMRVDRV_ADAPTER)MiniportAdapterContext;
    DBGPRINT(DBG_TX, (L"+MrvDrvSend()\n")); 
  //  printf ("+MrvDrvSend()\n");
    
    // In Deep Sleep Mode no packet can be sent out 
    //012207
    //if (Adapter->IsDeepSleep)
    if( !IsThisDsState(Adapter, DS_STATE_NONE) )
    {
      //Status = NDIS_STATUS_NO_CABLE;
      return NDIS_STATUS_FAILURE;
    }
  
    //      Check device removal status
    if( Adapter->SurpriseRemoved == TRUE )    
    {   
        DBGPRINT(DBG_TX|DBG_WARNING,(TEXT("[MrvSend]: NDIS_STATUS_FAILURE by supriseRemoved\r\n")));
        return NDIS_STATUS_FAILURE;
    }

    if( Adapter->bIsPendingReset == TRUE || Adapter->ChipResetting == 1)
    {                         
        DBGPRINT(DBG_TX|DBG_CMD|DBG_WARNING,(L"[MrvSend]: NDIS RETURN FAILURE by bIsPendingReset or ChipReset\r\n"));
        return NDIS_STATUS_FAILURE;
    }


    if ( Adapter->MediaConnectStatus == NdisMediaStateDisconnected )
    {
        DBGPRINT(DBG_TX|DBG_WARNING, (L"***WARNING: OS attempted to send packet while disconnected!\r\n"));
        
        if (IsIndicateDisconnect(Adapter) == TRUE) {
            Ndis_MediaStatus_Notify(Adapter,NDIS_STATUS_MEDIA_DISCONNECT); 
        } else {
            NdisMSleep(100000);     ///Sleep 100ms temporally
        }
        //dralee_20060712
        ResetAllScanTypeAndPower(Adapter);
        CleanUpSingleTxBuffer(Adapter);
        ResetRxPDQ(Adapter); 
        return NDIS_STATUS_FAILURE;
    }                       

    if( Adapter->bIsScanInProgress == TRUE ) {
        return NDIS_STATUS_SUCCESS;
    }

	*((ULONG *)(&Packet->MacReserved[0])) = GetTickCount();


    // check if in key absent state, if so, block all packet other than
    // 802.1x
    if ( (Adapter->EncryptionStatus == Ndis802_11Encryption2KeyAbsent )|| (Adapter->EncryptionStatus == Ndis802_11Encryption3KeyAbsent ) )  
    {
    pTxNode = &Adapter->TxNode;
        
    NdisQueryPacket( 
            Packet,
            NULL,
            &BufferCount,
            &pBuffer,
            &TotalPacketLength );

      if (!pBuffer || !BufferCount || !TotalPacketLength)
      {
        return NDIS_STATUS_FAILURE;
        
      }

       NdisQueryBuffer(pBuffer, &pVirtualAddr, &Length);
       pHeader = (PUCHAR)pVirtualAddr;

         if ( TotalPacketLength < 14 ) 
        {
            // malformed packet, blocked!
            DBGPRINT(DBG_TX|DBG_WARNING,(L"Got packet with size less than 14 bytes, reject!\n"));
            return NDIS_STATUS_FAILURE;
        }

        if ( (pHeader[12] != 0x88) || (pHeader[13] != 0x8E) )
        {
            DBGPRINT(DBG_TX|DBG_WARNING,(L"Still no key and packet type(0x%x 0x%x)is not 802.1x , drop!\n",
                                  pHeader[12],
                                  pHeader[13]));
            return NDIS_STATUS_FAILURE;
        }
     }// if ( (Adapter->EncryptionStatus == Ndis802_11Encryption2KeyAbsent )|| (Adapter->EncryptionStatus == Ndis802_11Encryption3KeyAbsent ) )  
                       
if(Adapter->TCloseWZCFlag==WZC_Ignore_Send_EAPOL_START)
{
 if ( (Adapter->EncryptionStatus == Ndis802_11Encryption2Enabled )||(Adapter->EncryptionStatus == Ndis802_11Encryption2KeyAbsent )||(Adapter->EncryptionStatus == Ndis802_11Encryption3Enabled )||(Adapter->EncryptionStatus == Ndis802_11Encryption3KeyAbsent )  )  
    {
        pTxNode = &Adapter->TxNode;
        
        NdisQueryPacket( 
            Packet,
            NULL,
            &BufferCount,
            &pBuffer,
            &TotalPacketLength );

      if (!pBuffer || !BufferCount || !TotalPacketLength)
      {
        return NDIS_STATUS_FAILURE;
        
      }

       NdisQueryBuffer(pBuffer, &pVirtualAddr, &Length);
       pHeader = (PUCHAR)pVirtualAddr;


        if ( (pHeader[12] == 0x88) && (pHeader[13] == 0x8E)&& (pHeader[14] == 0x01) &&(pHeader[15] == 0x01) )
        {
            DBGPRINT(DBG_TX|DBG_HELP,(L"Temporary don't send EAPOL-start!!EncryptionStatus=0x%x, (0x%x, 0x%x, 0x%x, 0x%x)\n",
                                  Adapter->EncryptionStatus, 
			             pHeader[12],
                                  pHeader[13],
                                  pHeader[14],
                                  pHeader[15]));
            return NDIS_STATUS_SUCCESS;
        }
 	}
}
        
        EnterCriticalSection(&Adapter->TxCriticalSection);

        if(Adapter->TxPacketCount >= (MAX_TX_PACKETS-1) )
        {   
             UCHAR sts;    
             //DBGPRINT(DBG_ERROR,(L"Tx queue is still full (count=%d), return FAILURE for this packet\r\n",Adapter->TxPacketCount));

             sts = TxPacketEnQueue(Adapter, Packet);

             if( sts == TRUE ) //101607 
             {
                 Adapter->TxPacketCount++;  
                 LeaveCriticalSection(&Adapter->TxCriticalSection);   
                 return NDIS_STATUS_SUCCESS;    
             }
             else if ( sts == EQ_REPLACE_QUEUE )
             { 
                 LeaveCriticalSection(&Adapter->TxCriticalSection); 
                 DBGPRINT(DBG_ERROR,(L"Replace a queued packet:%d\n\r",Adapter->TxPacketCount));
                 return NDIS_STATUS_SUCCESS;    
             }  
             else
             {  
                 LeaveCriticalSection(&Adapter->TxCriticalSection); 
                 //NdisMSleep(2000);   
                 DBGPRINT(DBG_ERROR,(L"Throw out current packet:%d\n\r",Adapter->TxPacketCount));  
                 //return success otherwise the endpoint may retransmit this packet that low down the throughput.
                 return NDIS_STATUS_SUCCESS;    
             }
        } 
                                   
        //record how many tx pkt is sent.   
        Adapter->TxPacketSend++;  
    
        DBGPRINT(DBG_TX|DBG_HELP,(L"[Marvell:MrvDrvSend] Adapter->TxPacketSend=%d\n", Adapter->TxPacketSend));    


        if ( TxPacketEnQueue(Adapter, Packet) != TRUE)
        {
            LeaveCriticalSection(&Adapter->TxCriticalSection);
            return NDIS_STATUS_SUCCESS;
        }
        
        Adapter->TxPacketCount++; 

        LeaveCriticalSection(&Adapter->TxCriticalSection);

        if ( Adapter->SentPacket == NULL && Adapter->TxLock == 0 )
        {
            // Fire TxThread!
            Adapter->SoftIntStatus |= MRVL_SOFT_INT_TxRequest;
            SetEvent(Adapter->hControllerInterruptEvent);
        }

        return NDIS_STATUS_SUCCESS;
        

    return Status;
} 