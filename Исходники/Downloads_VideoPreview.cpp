void CDownloads_VideoPreview::Play()
{
    USES_CONVERSION;

    if (m_bUsingVideo2)
        return;

    if (m_wndVideo.m_player.Get_State () != VFPS_CLOSED)
    {
        if (m_wndVideo.m_player.Get_State () != VFPS_RUNNING)
            m_wndVideo.m_player.Run ();
        return;
    }

    if (m_pActiveDownload)
    {
        HRESULT hr = E_FAIL;
        BOOL bWasErrMsg = FALSE;


        if (S_FALSE == CoInitialize (NULL))
            CoUninitialize ();

        if (m_pActiveDownload->pMgr->IsDone ())
        {
            hr = m_wndVideo.m_player.Open2 (m_pActiveDownload->pMgr->get_OutputFilePathName ());

            if (FAILED (hr))
            {
                fsString strFile = m_pActiveDownload->pMgr->get_OutputFilePathName ();
                LPCSTR psz = strrchr (strFile, '.');
                if (psz++)
                {
                    if (lstrcmpi (psz, "flv") == 0)
                    {
                        CRect rc (0,0,0,0);
                        m_wndVideo.GetWindowRect (&rc);
                        ScreenToClient (&rc);
                        m_wndVideo2.Create (NULL, WS_CHILD, rc, this, 0x111a);
                        m_wndVideo2.SetBackgroundColor (0);
                        m_wndVideo2.LoadMovie (0, ((CFdmApp*)AfxGetApp ())->m_strAppPath + "player.swf");

                        m_wndVideo.ShowWindow (SW_HIDE);
                        m_wndVideo2.ShowWindow (SW_SHOW);
                        m_bUsingVideo2 = TRUE;

                        CString str;
                        str = "<invoke name=\"loadAndPlayVideo\" returntype=\"xml\">";
                        str += "<arguments><string>";
                        str += strFile;
                        str += "</string></arguments></invoke>";
                        m_wndVideo2.CallFunction (str);

                        hr = S_OK;
                    }
                }
            }


        }
        else
        {
            UINT64 nAvail = Get_AvailFileSize ();

            if (nAvail)
            {
                if (FALSE == OpenFile ())
                {
                    hr = E_FAIL;
                    bWasErrMsg = TRUE;
                }
                else
                    hr = m_wndVideo.m_player.Open (m_hFile, nAvail);

                if (FAILED (hr) && bWasErrMsg == FALSE)
                {
                    CloseFile ();
                    hr = m_wndVideo.m_player.Open2 (m_pActiveDownload->pMgr->get_OutputFilePathName ());
                }
            }
            else
                bWasErrMsg = TRUE;
        }

        if (FAILED (hr))
        {
            CloseFile ();

            if (bWasErrMsg == FALSE)
            {
                if (m_dwDXVersion == 0)
                    m_dwDXVersion = fsDirectXVersion::GetCurrentVersion ();

                if (m_dwDXVersion < 0x0800)
                {
                    CString strErr = LS (L_FAILEDTOOPENFILE);
                    strErr += "\n\n";
                    strErr += LS (L_NEEDDX8ORBETTER);
                    MessageBox (strErr, LS (L_ERR), MB_ICONERROR);
                }
                else
                {
                    CString strErr = LS (L_FAILEDTOOPENFILE);
                    strErr += "\n\n";
                    strErr += LS (L_UNKMEDIATYPE);
                    MessageBox (strErr, LS (L_ERR), MB_ICONERROR);
                }
            }

            m_vidseek.Set_MediaSeeking (NULL);
            return;
        }

        if (m_bUsingVideo2 == FALSE)
        {
            IMediaSeeking* pMS = Get_Player ()->Get_MediaSeeking ();
            m_vidseek.Set_MediaSeeking (pMS);
            if (pMS)
                pMS->Release ();

            m_wndVideo.m_player.Run ();
            m_vidman.ApplyVolumeSettings ();
        }
    }
}