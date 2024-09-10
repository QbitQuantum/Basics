/**
* @brief         Sends STCAN_MSG structure from the client dwClientID.
* @param[in]     dwClientID is the client ID
* @param[in]     sMessage is the application specific CAN message structure
* @return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_VSCOM::sendMessage(DWORD dwClientID, const STCAN_MSG& sMessage)
{
    VSCAN_MSG msg;
    DWORD dwTemp;
    static SACK_MAP sAckMap;
    HRESULT hResult;

    VALIDATE_VALUE_RETURN_VAL(sg_bCurrState, STATE_CONNECTED, ERR_IMPROPER_STATE);

    hResult = S_FALSE;
    if (bClientIdExist(dwClientID))
    {
        if (sMessage.m_ucChannel <= sg_nNoOfChannels)
        {
            memset(&msg, 0, sizeof(msg));

            if (sMessage.m_ucEXTENDED == 1)
            {
                msg.Flags |= VSCAN_FLAGS_EXTENDED;
            }
            if (sMessage.m_ucRTR == 1)
            {
                msg.Flags |= VSCAN_FLAGS_REMOTE;
            }
            msg.Id = sMessage.m_unMsgID;
            msg.Size = sMessage.m_ucDataLen;
            memcpy(msg.Data, &sMessage.m_ucData, msg.Size);
            sAckMap.m_ClientID = dwClientID;
            sAckMap.m_Channel  = sMessage.m_ucChannel;
            sAckMap.m_MsgID    = msg.Id;
            vMarkEntryIntoMap(sAckMap);
            if (VSCAN_Write(sg_VSCanCfg.hCan, &msg, 1, &dwTemp) == VSCAN_ERR_OK && dwTemp == 1)
            {
                static STCANDATA can_data;
                CopyMsg2CanData(&can_data, &msg, TX_FLAG);
                EnterCriticalSection(&sg_DIL_CriticalSection);
                //Write the msg into registered client's buffer
                vWriteIntoClientsBuffer(can_data);
                LeaveCriticalSection(&sg_DIL_CriticalSection);
                hResult = S_OK;
            }
            else
            {
                hResult = S_FALSE;
                sg_pIlog->logMessage(A2T(__FILE__), __LINE__, _("could not write can data into bus"));
            }
        }
        else
        {
            hResult = ERR_INVALID_CHANNEL;
        }
    }
    else
    {
        hResult = ERR_NO_CLIENT_EXIST;
    }
    return(hResult);
}