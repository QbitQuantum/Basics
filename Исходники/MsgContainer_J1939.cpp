/******************************************************************************
    Function Name    :  vProcessNewData
    Input(s)         :  sJ1939Msg
    Output           :
    Functionality    :  Process a new Rx/Tx msg
    Member of        :  CMsgContainerJ1939
    Friend of        :      -
    Author(s)        :  Arun kumar K
    Date Created     :  31.01.2010
******************************************************************************/
void CMsgContainerJ1939::vProcessNewData(STJ1939_MSG& sJ1939Msg)
{

    // append : 1. Add item, get count, SetItemCount.
    // OW     : 1. Get ID, Create map index, Search if it is present in map
    //             if present change the offset and time stamp
    //          2. if not present and (get count < max count) save the Buffer index,
    //             ListCtrl index, time stamp, make offest = time stamp in disp entry
    //             and add to the map and array
    //          3. if not present and (get count = max count), do nothing
    //          4. SetItemcount

    if ( !bIsErrorMsg(sJ1939Msg.m_sMsgProperties.m_eType)  )
    {

        // Add to append buffer
        // If its the very first entry, the time stamp must
        if (m_sJ1939ReadMsgSpl.m_sMsgProperties.m_un64TimeStamp != 0) // be 0 and will
        {
            // retain such value.
            m_sJ1939ReadMsgSpl.m_nDeltime = _abs64( sJ1939Msg.m_sMsgProperties.m_un64TimeStamp -
                                                    m_sJ1939ReadMsgSpl.m_sMsgProperties.m_un64TimeStamp);
        }
        static BYTE arrBuf[MAX_MSG_LEN_J1939 + sizeof(__int64)];

        if (!bTobeBlocked(sJ1939Msg))
        {
            sJ1939Msg.vGetDataStream(arrBuf);
            m_sJ1939ReadMsgSpl.vSetDataStream(arrBuf);
            m_sJ1939ReadMsgSpl.vGetDataStream(arrBuf);
            m_ouAppendJ1939Buf.WriteIntoBuffer(J1939, arrBuf/*(BYTE*)&m_sJ1939ReadMsgSpl*/, m_sJ1939ReadMsgSpl.nGetSize());

            if (nullptr != m_pRxMsgCallBack)
            {
                m_pRxMsgCallBack->onRxMsg((void*)&sJ1939Msg);
            }
        }
    }
    //else //Add the error messages
    //{
    //    vProcessCurrErrorEntry(sCanData.m_uDataInfo.m_sErrInfo);
    //    // Add to append buffer
    //    // If its the very first entry, the time stamp must
    //    if (m_sCANReadDataSpl.m_lTickCount.QuadPart != 0) // be 0 and will
    //    {                                                     // retain such value.
    //        m_sCANReadDataSpl.m_nDeltime = sCanData.m_lTickCount.QuadPart -
    //                                       m_sCANReadDataSpl.m_lTickCount.QuadPart;
    //    }
    //    STCANDATA *pStcan = &m_sCANReadDataSpl;
    //    *pStcan = sCanData;
    //    m_ouAppendCanBuf.WriteIntoBuffer(&m_sCANReadDataSpl);

    //    if (nullptr != m_pRxMsgCallBack)
    //    {
    //        m_pRxMsgCallBack((void*)&sCanData, CAN);
    //    }
    //}
}