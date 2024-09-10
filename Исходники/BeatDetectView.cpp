HRESULT CBeatDetectView::CreateStreamsList
(
    CList<CDataStream*,CDataStream*> *pList
)
{
    CBeatDetectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    if( NULL == pList )
        return E_INVALIDARG;

    CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
    CDialogBar* pDlgBar  = pMainFrm->GetDialogBar();

    // Clear out list
    while( !pList->IsEmpty() )
        pList->RemoveTail();
    
    if( ((CButton*)pDlgBar->GetDlgItem(IDC_VIEW_INPUT_CHECK))->GetCheck() )
    {
        pList->AddTail( &pDoc->m_ASInput );
    }

    if( ((CButton*)pDlgBar->GetDlgItem(IDC_VIEW_ONSET_CHECK))->GetCheck() )
    {
        pList->AddTail( &pDoc->m_StrmOnsetOutput );
    }

    if( ((CButton*)pDlgBar->GetDlgItem(IDC_VIEW_ONSET2_CHECK))->GetCheck() )
    {
        pList->AddTail( &pDoc->m_StrmOnsetInternal );
    }

    if( ((CButton*)pDlgBar->GetDlgItem(IDC_VIEW_BEATOUT_CHECK))->GetCheck() )
    {
        pList->AddTail( &pDoc->m_StrmBeatOutput );
    }

    if( ((CButton*)pDlgBar->GetDlgItem(IDC_VIEW_TEMPOOUT_CHECK))->GetCheck() )
    {
        pList->AddTail( &pDoc->m_StrmBeatTempo );
    }

    if( ((CButton*)pDlgBar->GetDlgItem(IDC_VIEW_PERIODOUT_CHECK))->GetCheck() )
    {
        pList->AddTail( &pDoc->m_StrmBeatPeriod );
    }

    if( ((CButton*)pDlgBar->GetDlgItem(IDC_VIEW_INFOOUT_CHECK))->GetCheck() )
    {
        pList->AddTail( &pDoc->m_StrmBeatInfo );
    }

    if( !pList->IsEmpty() )
        return S_OK;
    else
        return S_FALSE;
}