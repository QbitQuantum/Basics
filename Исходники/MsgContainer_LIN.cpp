/******************************************************************************
    Function Name    :  vProcessNewData
    Input(s)         :
    Output           :
    Functionality    :  Process a new Rx/Tx msg
    Member of        :  CMsgContainerLIN
    Friend of        :      -
    Author(s)        :  Anish kumar
    Date Created     :  01.04.2010
******************************************************************************/
void CMsgContainerLIN::vProcessNewData(STLINDATA& sLinData)
{

    // append : 1. Add item, get count, SetItemCount.
    // OW     : 1. Get ID, Create map index, Search if it is present in map
    //             if present change the offset and time stamp
    //          2. if not present and (get count < max count) save the Buffer index,
    //             ListCtrl index, time stamp, make offest = time stamp in disp entry
    //             and add to the map and array
    //          3. if not present and (get count = max count), do nothing
    //          4. SetItemcount

    if ( IS_A_MESSAGE(sLinData.m_ucDataType) )
    {

        // Add to append buffer
        // If its the very first entry, the time stamp must
        if (m_sLINReadDataSpl.m_lTickCount.QuadPart != 0) // be 0 and will
        {
            // retain such value.
            m_sLINReadDataSpl.m_nDeltime = _abs64(sLinData.m_lTickCount.QuadPart -
                                                  m_sLINReadDataSpl.m_lTickCount.QuadPart);
        }

        STLINDATA* pStlin = &m_sLINReadDataSpl;
        *pStlin = sLinData;
        if (!bTobeBlocked(sLinData))
        {
            m_ouAppendLinBuf.WriteIntoBuffer(&m_sLINReadDataSpl);

            if (NULL != m_pRxMsgCallBack)
            {
                m_pRxMsgCallBack((void*)&sLinData, LIN);
            }
        }
    }
    else //Add the error messages
    {
        vProcessCurrErrorEntryLin(sLinData.m_uDataInfo.m_sErrInfo);
        // Add to append buffer
        // If its the very first entry, the time stamp must
        if (m_sLINReadDataSpl.m_lTickCount.QuadPart != 0) // be 0 and will
        {
            // retain such value.
            m_sLINReadDataSpl.m_nDeltime = _abs64(sLinData.m_lTickCount.QuadPart -
                                                  m_sLINReadDataSpl.m_lTickCount.QuadPart);
        }
        STLINDATA* pStlin = &m_sLINReadDataSpl;
        *pStlin = sLinData;
        m_ouAppendLinBuf.WriteIntoBuffer(&m_sLINReadDataSpl);

        if (NULL != m_pRxMsgCallBack)
        {
            m_pRxMsgCallBack((void*)&sLinData, LIN);
        }
    }

}