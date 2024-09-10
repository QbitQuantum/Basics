void
CConfigDisplay::setupSample() {
    UpdateData(TRUE);
    m2v();
    copy2lf(m_samplelfTitles,m_samplelfPanel,m_samplelfColHdr/*,m_samplelfCurPlay*/);

    static int first = 1;
    if (first) {
        first = 0;
        m_SamplePlaylist.initFont();
    }

    COLORREF crTransMain,crTransPanel;
    MBCONFIG_READ_TRANS_COLORS(m_regSD,crTransMain,crTransPanel);

    // Column Header
    m_FontSampleColHdr.DeleteObject();
    m_FontSampleColHdr.CreateFontIndirect(&m_samplelfColHdr);
    m_SampleColHdr.SetFont(&m_FontSampleColHdr, TRUE);
    m_SampleColHdr.changeFont(&m_FontSampleColHdr);
    m_SampleColHdr.setText("Artists");

    m_SampleColHdr.SetColors(m_vTxColHdr, m_vBkColHdr,
                             m_vcrColHdrInUL,m_vcrColHdrInLR,m_vcrColHdrOutUL,m_vcrColHdrOutLR,
                             m_3dColHdr);

    CRect rectColHdr;
    m_SampleColHdr.GetWindowRect(rectColHdr);
    ScreenToClient(rectColHdr);

    // Data Window
    CRect rectData,rectDataNew;
    m_SamplePlaylist.GetWindowRect(rectData);
    ScreenToClient(rectData);

    rectDataNew = rectColHdr;
    rectDataNew.top = rectColHdr.bottom;
    rectDataNew.bottom = rectDataNew.top + rectData.Height();
    rectDataNew.right = (rectDataNew.left + rectColHdr.Width());

    CDC * cdc = GetDC();
    LPLOGFONT lplf = &m_samplelfTitles;
    m_SamplePlaylist.changeFont(lplf);

    // Status
    CRect rectStatus,rectStatusNew;
    m_SamplePanel.GetWindowRect(rectStatus);
    ScreenToClient(rectStatus);

    rectStatusNew = rectColHdr;
    rectStatusNew.top = rectDataNew.bottom+5;
    rectStatusNew.bottom = rectStatusNew.top + rectStatus.Height();

    m_FontSamplePanel.DeleteObject();
    m_FontSamplePanel.CreateFontIndirect(&m_samplelfPanel);
    m_SamplePanel.SetFont(&m_FontSamplePanel, TRUE);
    m_SamplePanel.changeFont(&m_FontSamplePanel);
    m_SamplePanel.setText("01:30/03:29 Howling Fish by Big Fish Howlers");
    m_SamplePanel.SetTicking(TRUE);

    m_SamplePanel.SetColors(m_vTxPanel,m_vBkPanel,\
                            m_vcrStatusInUL,m_vcrStatusInLR,m_vcrStatusOutUL,m_vcrStatusOutLR,\
                            m_3dStatus);
    m_SamplePanel.MoveWindow(rectStatusNew);

    m_SamplePlaylist.ResetContent();
    m_SamplePlaylist.AddString(" all");
    m_SamplePlaylist.AddString("Little Twisty Big Fun Band");
    m_SamplePlaylist.AddString("Twisty Little Big Fun Band");
    m_SamplePlaylist.AddString("Big Fun Little Twisty Band");
    m_SamplePlaylist.AddString("Fun Big Little Twisty Band");
    m_SamplePlaylist.AddString("Band O Little Twisty Big Fun Folks");
    m_SamplePlaylist.AddString("Little Twisty Big Fun Band O Folks");
    m_SamplePlaylist.AddString("Twisty Fun Big Band O Littles");
    m_SamplePlaylist.AddString("Xyzzy");
    m_SamplePlaylist.AddString("Big Little Band O Little Twisties");
    m_SamplePlaylist.AddString("Plugh");
    m_SamplePlaylist.AddString("Did you get the memo about the new cover sheets for our TPS Reports?");
    m_SamplePlaylist.AddString("There is an Easter Egg on the about screen.");

    m_SamplePlaylist.MoveWindow(rectDataNew);
    m_SamplePlaylist.SetBitmaps(cdc,
                                getSkin(MB_SKIN_SCROLLUPARROW),crTransPanel,
                                getSkin(MB_SKIN_SCROLLDOWNARROW),crTransPanel,
                                getSkin(MB_SKIN_SCROLLBUTTON),crTransPanel,
                                getSkin(MB_SKIN_SCROLLBACKGROUND),crTransPanel);
    m_SamplePlaylist.SetColors(m_vBkNormal,m_vBkHigh,m_vBkSel,
                               m_vTxNormal,m_vTxHigh,m_vTxSel,m_3dData,
                               m_vcrDataInUL,m_vcrDataInLR,m_vcrDataOutUL,m_vcrDataOutLR);

    ReleaseDC(cdc);

    CDIBSectionLite bmp;
    if (!bmp.Load(getSkin(MB_SKIN_BACKGROUNDLIBRARY))) {
        m_SampleColHdr.RedrawWindow();
        m_SamplePanel.RedrawWindow();
        m_SamplePlaylist.invalidate();
        m_SamplePlaylist.RedrawWindow();
        return;
    }

    CRect grect;
    grect.UnionRect(rectColHdr,rectStatusNew);
    grect.InflateRect(10,10,10,10);
    CDC * dc = GetDC();

    LayOutStyle BackgroundMainType,BackgroundPanelType;
    MBCONFIG_READ_BACKGROUND_TYPES(m_regSD,BackgroundMainType,BackgroundPanelType);

    BitmapToCRect bmcr((HBITMAP)bmp, grect, BackgroundPanelType,
                       bmp.GetWidth(), bmp.GetHeight());

//	dc->FillSolidRect(grect, RGB(0,255,0));
    MBUtil::BmpToDC(dc, &bmcr, TRUE, crTransPanel, 0);

    ReleaseDC(dc);
    m_SampleColHdr.RedrawWindow();
    m_SamplePanel.RedrawWindow();

    m_SamplePlaylist.invalidate();
    m_SamplePlaylist.RedrawWindow();


}