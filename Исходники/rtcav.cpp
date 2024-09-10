HRESULT CRTCAVSession::ShowVideo(RTC_VIDEO_DEVICE enDevice, BOOL fShow)
{
    IVideoWindow * pVid = NULL;
    IRTCClient * pClient = NULL;
    long lMediaCaps = 0;
    HWND hWnd = NULL;
    HRESULT hr;

    hr = m_pSession->get_Client(&pClient);

    if (FAILED(hr))
    {
        // get_Client failed
        return hr;
    }

    // Get the media capabilities
    hr = pClient->get_MediaCapabilities(&lMediaCaps);

    if (FAILED(hr))
    {
        // get_MediaCapabilities failed
        SAFE_RELEASE(pClient);
        return hr;
    }

    hr = pClient->get_IVideoWindow(
        enDevice, &pVid);

    SAFE_RELEASE(pClient);

    if (FAILED(hr))
    {
        // get_IVideoWindow failed
        return hr;
    }

    if (enDevice == RTCVD_PREVIEW)
    {          
        // Determine whether to show the preview video
        fShow = fShow && (lMediaCaps & RTCMT_VIDEO_SEND);
        m_fShowPrev = fShow;
        hWnd = m_hPrevVideoParent;

        // Show or hide the preview video preview parent window
        ShowWindow(m_hPrevVideoParent, fShow ? SW_SHOW : SW_HIDE);

        // Set window region for receive video parent window        
        HRGN hRegion;

        if (fShow)
        {
            // Set the receive video region to make room for the preview
            // video picture-in-picture
            POINT rgPoints[6] =
                    { 0, 0,
                      0, m_lRecvHeight,
                      m_lRecvWidth - m_lPrevWidth, m_lRecvHeight,
                      m_lRecvWidth - m_lPrevWidth, m_lRecvHeight - m_lPrevHeight,
                      m_lRecvWidth, m_lRecvHeight - m_lPrevHeight,
                      m_lRecvWidth, 0
                    };

            hRegion = CreatePolygonRgn(rgPoints, 6, ALTERNATE);
        }
        else
        {
            // Set the receive video region to be rectangular
            hRegion = CreateRectRgn(0, 0, m_lRecvWidth, m_lRecvHeight);
        }

        SetWindowRgn(m_hRecvVideoParent, hRegion, TRUE);
    }
    else
    {
        // Determine whether to show the receive video        
        fShow = fShow && (lMediaCaps & RTCMT_VIDEO_RECEIVE);
        m_fShowRecv = fShow;
        hWnd = m_hRecvVideoParent;

        // Always show the video receive parent window
        ShowWindow(m_hRecvVideoParent, SW_SHOW);
    }

    if ( fShow == TRUE )
    {
        // Set the video window style
        pVid->put_WindowStyle( WS_CHILD |
                               WS_CLIPCHILDREN |
                               WS_CLIPSIBLINGS );
        
        // Set the parent window for the video window
        pVid->put_Owner( (OAHWND)hWnd );

        RECT rc;
        GetClientRect(hWnd, &rc );  
        
        // Position the video window
        pVid->SetWindowPosition(
            rc.left,
            rc.top,
            rc.right,
            rc.bottom
            );

        // Make the video window visible
        pVid->put_Visible(-1);        
    }       

    SAFE_RELEASE(pVid);    

    return S_OK;
}