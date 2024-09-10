void VolumeBrush::HandleTrigger(HOBJECT hSender, HSTRING hMsg)
{
    CServerDE* pServerDE = GetServerDE();
    if (!pServerDE) return;

    char* pMsg = pServerDE->GetStringData(hMsg);
    if (!pMsg || !pMsg[0]) return;

    DBOOL bToggle = DFALSE;

    if (_mbsicmp((const unsigned char*)pMsg, (const unsigned char*)TRIGGER_MSG_TOGGLE) == 0)
    {
        bToggle = DTRUE;
    }

    if ((bToggle && m_bHidden) || _mbsicmp((const unsigned char*)pMsg, (const unsigned char*)TRIGGER_MSG_ON) == 0)
    {
        DDWORD dwFlags;
        pServerDE->SetObjectFlags(m_hObject, m_dwSaveFlags);

        dwFlags = pServerDE->GetObjectUserFlags(m_hObject);
        pServerDE->SetObjectUserFlags(m_hObject, dwFlags | USRFLG_VISIBLE);

        if (m_hSurfaceObj)
        {
            dwFlags = pServerDE->GetObjectUserFlags(m_hSurfaceObj);
            pServerDE->SetObjectUserFlags(m_hSurfaceObj, dwFlags | USRFLG_VISIBLE);
        }

        m_bHidden = DFALSE;
    }
    else if ((bToggle && !m_bHidden) || _mbsicmp((const unsigned char*)pMsg, (const unsigned char*)TRIGGER_MSG_OFF) == 0)
    {
        DDWORD dwFlags;
        pServerDE->SetObjectFlags(m_hObject, m_dwSaveFlags & ~FLAG_VISIBLE);

        dwFlags = pServerDE->GetObjectUserFlags(m_hObject);
        pServerDE->SetObjectUserFlags(m_hObject, dwFlags & ~USRFLG_VISIBLE);

        if (m_hSurfaceObj)
        {
            dwFlags = pServerDE->GetObjectUserFlags(m_hSurfaceObj);
            pServerDE->SetObjectUserFlags(m_hSurfaceObj, dwFlags & ~USRFLG_VISIBLE);
        }

        m_bHidden = DTRUE;
    }
}