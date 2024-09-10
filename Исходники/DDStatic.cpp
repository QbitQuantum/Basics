  DROPEFFECT StartDragging(RECT *rClient)
  {
    //pws_os::Trace(L"CStaticDataSource::StartDragging\n");

    DelayRenderData(CF_UNICODETEXT);
    DelayRenderData(CF_TEXT);

    //pws_os::Trace(L"CStaticDataSource::StartDragging - calling DoDragDrop\n");
    DROPEFFECT dropEffect = DoDragDrop(DROPEFFECT_COPY, rClient, m_pDropSource);

    //pws_os::Trace(L"CStaticDataSource::StartDragging - returned from DoDragDrop, dropEffect=%d\n",
    //  dropEffect);

    if (m_DDstatic.m_hgDataTXT != NULL) {
      //pws_os::Trace(L"CStaticDataSource::StartDragging - Unlock/Free m_hgDataTXT\n");
      GlobalUnlock(m_DDstatic.m_hgDataTXT);
      GlobalFree(m_DDstatic.m_hgDataTXT);
      m_DDstatic.m_hgDataTXT = NULL;
    }

    if (m_DDstatic.m_hgDataUTXT != NULL) {
      //pws_os::Trace(L"CStaticDataSource::StartDragging - Unlock/Free m_hgDataUTXT\n");
      GlobalUnlock(m_DDstatic.m_hgDataUTXT);
      GlobalFree(m_DDstatic.m_hgDataUTXT);
      m_DDstatic.m_hgDataUTXT = NULL;
    }
    return dropEffect;
  }