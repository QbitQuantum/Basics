void CADQIDlg::OnDblClkInterfaces()
{
    CString s;
    int xx=0;
    int idx;
    IUnknown *pNewUnk = NULL;


    idx = m_cListIf.GetCurSel();
    if ( idx == LB_ERR )
    {
        MessageBeep(0);
        return;
    }


    CWaitCursor wait;
    m_cListIf.GetText( idx, s );


    //////////////////////////////////////////////////////////////
    //
    // Find the appropriate dialog box to display
    //
    /////////////////////////////////////////////////////////////////
    while( !IsEqualIID( *adsiIfs[xx].pIID, IID_NULL ) && s != adsiIfs[xx].szIf  )
    {
        xx++;
    }

    ASSERT( !IsEqualIID( *adsiIfs[xx].pIID, IID_NULL ) );
    if ( adsiIfs[xx].pFn )
    {
        m_pUnk->AddRef();
        (*adsiIfs[xx].pFn)( m_pUnk, &pNewUnk );
    }
    else
    {
        wait.Restore();
        AfxMessageBox(_T("No UI implemented yet"));
    }



    ////////////////////////////////////////////////////
    // if IADsOpenObject is selected, special care
    ///////////////////////////////////////////////////
    if ( pNewUnk )
    {

        HRESULT hr;
        BSTR  bstr;
        IADs  *pADs;

        hr = pNewUnk->QueryInterface( IID_IADs, (void**) &pADs );
        if ( SUCCEEDED(hr) )
        {
            pADs->get_ADsPath( &bstr );
        }
        pADs->Release();

        m_sADsPath = bstr;
        SysFreeString( bstr );


        m_pUnk->Release(); // old ads iunknown path;
        m_pUnk = pNewUnk;

        UpdateData(FALSE);
        EnumerateInterface();

    }


}