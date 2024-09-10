//*****************************************************************************
//*****************************************************************************
__checkReturn
HRESULT
CMiniMdRW::StartENCMap()        // S_OK or error.
{
    HRESULT hr = S_OK;
    ULONG   iENC;               // Loop control.
    ULONG   ixTbl;              // A table.
    int     ixTblPrev = -1;     // Table previously seen.

    _ASSERTE(m_rENCRecs == 0);

    if (m_Schema.m_cRecs[TBL_ENCMap] == 0)
        return S_OK;

    // Build an array of pointers into the ENCMap table for fast access to the ENCMap
    //  for each table.
    m_rENCRecs = new (nothrow) ULONGARRAY;
    IfNullGo(m_rENCRecs);
    if (!m_rENCRecs->AllocateBlock(TBL_COUNT))
        IfFailGo(E_OUTOFMEMORY);
    for (iENC = 1; iENC <= m_Schema.m_cRecs[TBL_ENCMap]; ++iENC)
    {
        ENCMapRec *pMap;
        IfFailGo(GetENCMapRecord(iENC, &pMap));
        ixTbl = TblFromRecId(pMap->GetToken());
        _ASSERTE((int)ixTbl >= ixTblPrev);
        _ASSERTE(ixTbl < TBL_COUNT);
        _ASSERTE(ixTbl != TBL_ENCMap);
        _ASSERTE(ixTbl != TBL_ENCLog);
        if ((int)ixTbl == ixTblPrev)
            continue;
        // Catch up on any skipped tables.
        while (ixTblPrev < (int)ixTbl)
        {
            (*m_rENCRecs)[++ixTblPrev] = iENC;
        }
    }
    while (ixTblPrev < TBL_COUNT-1)
    {
        (*m_rENCRecs)[++ixTblPrev] = iENC;
    }

ErrExit:
    return hr;
} // CMiniMdRW::StartENCMap