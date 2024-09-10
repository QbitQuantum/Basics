void CUSBLogView::OnEditPaste(void) 
{
    if(!IsClipboardFormatAvailable(GetApp().m_uClipboardFormat))
    {
        TRACE("OnEditPaste(): no suitable clipboard format available!\n");
        return;
    }

    // we need a focused URB as well...
    int nFocusedURB = m_Log.FindFocusedURB();
    if(-1 == nFocusedURB)
    {
        nFocusedURB = 0;
    }

    if(!AfxGetMainWnd()->OpenClipboard())
    {
        TRACE("Error while opening clipboard!\n");
        return;
    }
    // from here on, we have to close the clipboard
    // before exiting this function, otherwise other
    // applications might not get a chance to copy/paste
    // stuff!
    HANDLE hBinary = NULL;
    PVOID pData = NULL;
    try
    {
        hBinary = GetClipboardData(GetApp().m_uClipboardFormat);
        if(NULL == hBinary)
        {
            AfxThrowNotSupportedException();
        }

        pData = GlobalLock(hBinary);
        {
            CMyMemFile memFile(pData);
            CArchive ar(&memFile, CArchive::load);
            DWORD dwVersion = ar.ReadCount();
            if(_VERSION_DWORD_ != dwVersion)
            {
                AfxThrowNotSupportedException();
            }

            DWORD nURBCnt = ar.ReadCount();
            TRACE("Pasting %d URBs...\n", nURBCnt);
            
            CUSBLogDoc *pDoc = GetDocument();
            int nInsertLocation = nFocusedURB;
            while(0 < nURBCnt)
            {
                CRuntimeClass *pClass = ar.ReadClass();
                if(!pClass->IsDerivedFrom(RUNTIME_CLASS(CURB)))
                {
                    TRACE("unknown runtime class!\n");
                    AfxThrowArchiveException(CArchiveException::badClass);
                }

                CURB *pURB = (CURB*) pClass->CreateObject();
                ASSERT(NULL != pURB);
                pURB->SetChunkAllocator(&pDoc->m_arURB.m_ChunkAllocator);
                pURB->Serialize(ar);
                pDoc->m_arURB.InsertAt(nInsertLocation, pURB);
                nInsertLocation++;
                --nURBCnt;
            }
            pDoc->UpdateAllViews(NULL, 1);
            OnEditSelectNone();
            m_Log.SetFocusedURB(nFocusedURB);            
        }

        GlobalUnlock(hBinary);
        hBinary = NULL;

        CloseClipboard();
    }
    catch(...)
    {
        if((NULL != pData) && (NULL != hBinary))
        {
            GlobalUnlock(hBinary);
        }
        CloseClipboard();
        throw;
    }
}