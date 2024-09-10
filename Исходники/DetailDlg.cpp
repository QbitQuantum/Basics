LRESULT CDetailDlg::OnPreviewRClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
	// This method is called when user right-clicks the preview area.
	// We need to display popup menu.

	CErrorReportSender* pSender = CErrorReportSender::GetInstance();
	
    CPoint pt;
    GetCursorPos(&pt);

    CMenu menu;
    menu.LoadMenu(IDR_POPUPMENU);

    CMenu submenu = menu.GetSubMenu(1);
    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING;

    strconv_t strconv;
	CString sAuto = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewAuto"));
	CString sText = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewText"));
	CString sHex = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewHex"));
	CString sImage = pSender->GetLangStr(_T("DetailDlg"), _T("PreviewImage"));
	CString sEncoding = pSender->GetLangStr(_T("DetailDlg"), _T("Encoding"));

    mii.dwTypeData = sAuto.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_PREVIEW_AUTO, FALSE, &mii);

    mii.dwTypeData = sHex.GetBuffer(0);
    submenu.SetMenuItemInfo(ID_PREVIEW_HEX, FALSE, &mii);

    mii.dwTypeData = sText.GetBuffer(0);
    submenu.SetMenuItemInfo(ID_PREVIEW_TEXT, FALSE, &mii);

    mii.dwTypeData = sImage.GetBuffer(0);
    submenu.SetMenuItemInfo(ID_PREVIEW_IMAGE, FALSE, &mii);

    UINT uItem = ID_PREVIEW_AUTO;
    if(m_previewMode==PREVIEW_HEX)
        uItem = ID_PREVIEW_HEX;
    else if(m_previewMode==PREVIEW_TEXT)
        uItem = ID_PREVIEW_TEXT;
    else if(m_previewMode==PREVIEW_IMAGE)
        uItem = ID_PREVIEW_IMAGE;

    submenu.CheckMenuRadioItem(ID_PREVIEW_AUTO, ID_PREVIEW_IMAGE, uItem, MF_BYCOMMAND); 

    if(m_filePreview.GetPreviewMode()!=PREVIEW_TEXT)
    {
        submenu.DeleteMenu(5, MF_BYPOSITION);
        submenu.DeleteMenu(4, MF_BYPOSITION);
    }
    else
    {
        CMenuHandle TextEncMenu = submenu.GetSubMenu(5);
        mii.dwTypeData = sEncoding.GetBuffer(0);
        submenu.SetMenuItemInfo(5, TRUE, &mii);


        UINT uItem2 = ID_ENCODING_AUTO;
        if(m_textEncoding==ENC_AUTO)
            uItem2 = ID_ENCODING_AUTO;
        else if(m_textEncoding==ENC_ASCII)
            uItem2 = ID_ENCODING_ASCII;
        else if(m_textEncoding==ENC_UTF8)
            uItem2 = ID_ENCODING_UTF8;
        else if(m_textEncoding==ENC_UTF16_LE)
            uItem2 = ID_ENCODING_UTF16;
        else if(m_textEncoding==ENC_UTF16_BE)
            uItem2 = ID_ENCODING_UTF16BE;

        TextEncMenu.CheckMenuRadioItem(ID_ENCODING_AUTO, ID_ENCODING_UTF16BE, uItem2, MF_BYCOMMAND); 
    }

    submenu.TrackPopupMenu(TPM_LEFTBUTTON, pt.x, pt.y, m_hWnd);

    return 0;
}