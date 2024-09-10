VOID WINAPI CDialDlg::_RasDialFunc(UINT, RASCONNSTATE state, DWORD dwError)
{
    if (m_bNeedStop)
        return;

    if (m_pThis == NULL)
        return;

    m_bInRasFunc = TRUE;


    m_pThisRefs++;

    if (dwError && m_bNeedStop == FALSE)
    {
        switch (dwError)
        {
        case ERROR_LINE_BUSY:

            m_pThis->Log (LS (L_LINEBUSY));
            break;

        case ERROR_PORT_OR_DEVICE:
            m_pThis->Log (LS (L_HARDWAREFAILURE));
            break;

        case ERROR_NO_DIALTONE:
            m_pThis->Log (LS (L_NODIALTONE));
            break;

        case ERROR_AUTHENTICATION_FAILURE:
            m_pThis->Log (LS (L_INVLOGIN2));
            break;

        default:


            char szErr [256];
            fsRasGetErrorString (dwError, szErr, sizeof (szErr));
            m_pThis->Log (szErr);

            if (m_pThis->m_dial == NULL)
                m_pThis->Cancel ();
            else
            {

                m_pThis->PostMessage (WM_DIALDLG_ENDDIALOG, IDCANCEL);
                Release_pThis ();
            }
            Release_pThis ();
            m_bInRasFunc = FALSE;
            return;
        }


        fsRasHangUp (m_hConn);
        m_hConn = NULL;

        m_pThis->m_cAttempts++;

        if (m_pThis->m_dial)
        {

            if (m_pThis->m_dial->cAttempts > m_pThis->m_cAttempts)
            {

                m_pThis->SleepInterval ();
            }
            else
            {


                if (m_hConn)
                {
                    fsRasHangUp (m_hConn);
                    m_hConn = NULL;
                }
                m_pThis->PostMessage (WM_DIALDLG_ENDDIALOG, IDCANCEL);
                Release_pThis ();
                Release_pThis ();
                m_bInRasFunc = FALSE;
                return;
            }
        }

        if (m_bNeedStop == FALSE)
        {


            m_pThis->Log ("");
            CString str;
            str.Format ("%s... %s %d", LS (L_DIALING), LS (L_ATTEMPT), m_pThis->m_cAttempts+1);
            m_pThis->Log (str);


            fsRasDial (NULL, NULL, &m_pThis->m_rp, 0, _RasDialFunc, &m_hConn);
        }

        Release_pThis ();
        m_bInRasFunc = FALSE;
        return;
    }


    switch (state)
    {
    case RASCS_OpenPort:
        m_pThis->Log (LS (L_OPENPORT));
        break;

    case RASCS_ConnectDevice:
        m_pThis->Log (LS (L_DIALTOPROVIDER));
        break;

    case RASCS_DeviceConnected:
        m_pThis->Log (LS (L_CONNECTEDTOREMOTE));
        break;

    case RASCS_Authenticate:
        m_pThis->Log (LS (L_VERUSERANDPASS));
        break;

    case RASCS_Connected:
        RAS_STATS stat;
        stat.dwSize = sizeof (stat);


        if (fsSysGetOsMajorVersion () >= 5)

            fsSysGetConnectionStatistics (m_hConn, &stat);
        else
            stat.dwBps = UINT_MAX;


        if (m_pThis->m_dial && stat.dwBps < m_pThis->m_dial->dwHangupLess)
        {
            CString str;
            str.Format (LS (L_CONNSPEEDNOW), stat.dwBps);
            m_pThis->Log (str);
            m_pThis->Log (LS (L_HANGUPIT));
            fsRasHangUp (m_hConn);
            m_hConn = NULL;


            if (m_pThis->m_cAgains < m_pThis->m_dial->cAgains)
            {


                m_pThis->m_cAttempts = 0;
                m_pThis->Log ("");
                CString str;
                str.Format ("%s %d", LS (L_REPETITION), m_pThis->m_cAgains+1);
                m_pThis->Log (str);
                m_pThis->Log ("");
                str.Format ("%s... %s %d", LS (L_DIALING), LS (L_ATTEMPT), m_pThis->m_cAttempts+1);
                m_pThis->Log (str);
                fsRasDial (NULL, NULL, &m_pThis->m_rp, 0, _RasDialFunc, &m_hConn);
                m_pThis->m_cAgains++;
            }
            else
            {

                m_pThis->PostMessage (WM_DIALDLG_ENDDIALOG, IDCANCEL);
                if (m_hConn)
                {
                    fsRasHangUp (m_hConn);
                    m_hConn = NULL;
                }
                Release_pThis ();
            }
        }
        else
        {

            m_hConn = NULL;
            InternetAutodial (INTERNET_AUTODIAL_FORCE_ONLINE, NULL);
            m_pThis->PostMessage (WM_DIALDLG_ENDDIALOG, IDOK);
            Release_pThis ();
        }
        break;
    }

    Release_pThis ();
    m_bInRasFunc = FALSE;
}