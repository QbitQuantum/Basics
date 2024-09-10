HRESULT CMsgContainerCAN::GetMessageName(STCANDATA& sCANMsg, CString& msgName, bool formatHexForId)
{
    if (IS_ERR_MESSAGE(sCANMsg.m_ucDataType))
    {
        GetErrorInfo(sCANMsg, msgName);
    }
    else
    {
        //Message Name
        std::string strName = "";
        IFrame* pouFrame = nullptr;
        ERRORCODE eResult = mBmNetwork->GetFrame(CAN, 0, sCANMsg.m_uDataInfo.m_sCANMsg.m_unMsgID, nullptr, &pouFrame);
        if (EC_SUCCESS == eResult && nullptr != pouFrame)
        {
            pouFrame->GetName(strName);
            msgName = strName.c_str();
        }
        else
        {
            if (formatHexForId == true)
            {
                msgName.Format("0x%X", sCANMsg.m_uDataInfo.m_sCANMsg.m_unMsgID);
            }
            else
            {
                msgName.Format("%d", sCANMsg.m_uDataInfo.m_sCANMsg.m_unMsgID);
            }
        }
    }
    return S_OK;
}