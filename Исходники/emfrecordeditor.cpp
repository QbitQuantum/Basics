void EMFRecordEditorFrame::GetRecordListFromFile()
{
    HENHMETAFILE hMeta = ReadEnhMetaFile(m_file.GetFullPath(), GetHwnd());
    if (!hMeta)
        return;

    // get meta header
    if (GetEnhMetaFileHeader(hMeta, sizeof(g_hMetaHeader), &g_hMetaHeader) != 
        sizeof(ENHMETAHEADER))
        return;

    // init data touched by the callback
    FreeEMFStuff();
    g_pHandleTable = NULL;
    g_nHandles = 0;
    g_pMetaRecords = NULL;
    g_nRecords = 0;
    g_nRecordsMax = 0;
    m_pList->DeleteAllItems();

    // get the list of meta records
    EnumEnhMetaFile( NULL, 
                     hMeta, 
                     (ENHMFENUMPROC)EnumEnhMetafileProc, 
                     (LPVOID)m_pList, 
                     NULL );

    DeleteEnhMetaFile(hMeta);

    // update GUI
    m_pList->SetColumnWidth(0, wxLIST_AUTOSIZE);
    m_pList->SetColumnWidth(1, wxLIST_AUTOSIZE);

    SetStatusText(wxString::Format(wxT("%d records"), g_nRecords), 2);
}