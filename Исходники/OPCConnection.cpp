//------------------------------------------------------------------*
HRESULT COPCConnection::DoDisconnect()
{
    TRACE(_T("COPCConnection::DoDisconnect from %s\n"), (LPCTSTR)m_sMachineName);
    CSingleLock lock(&m_cs, TRUE);
    _ASSERTE(m_bConnected);
    m_bConnected = false;
    FILETIME timeNow;
    CoFileTimeNow(&timeNow);
    POSITION pos = m_activeItemList.GetHeadPosition();
    while (pos != NULL) {
        CComVariant Value;
        WORD quality;
        FILETIME time;
        CItem *pItem = m_activeItemList.GetNext(pos);
        pItem->m_hServer = 0;
        pItem->GetQVT(&Value, &quality, &time);
        quality = OPC_QUALITY_BAD;
        time = timeNow;
        pItem->SetQVT(Value, quality, time);
    }
    while (!m_removedItemList.IsEmpty()) {
        CItem *pItem = m_removedItemList.RemoveHead();
        pItem->Release();
    }
    while (!m_writeRequestList.IsEmpty()) {
        CWriteRequest *pRequest = m_writeRequestList.RemoveHead();
        pRequest->Release();
    }
    lock.Unlock();

    m_pSyncIO->Release();
    m_pSyncIO=NULL;
    m_pItemMgt->Release();
    m_pItemMgt=NULL;
    
    HRESULT hr = m_pOPCServer->RemoveGroup(m_hGroup1, TRUE);
    m_pOPCServer->Release();
    m_pOPCServer=NULL;

    return S_OK;
}