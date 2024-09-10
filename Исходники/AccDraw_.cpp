int DDInit(void)
{
        HRESULT hRet;

        hWnd = Form1->Handle;

        DDEnd();
        hRet = DirectDrawCreateEx(NULL, (VOID**)&m_pDD, IID_IDirectDraw7, NULL);
        if(DDError(hRet != DD_OK,"DDCreateEX")) return(false);

        if (Form1->FullScreen)
        {
                hRet = m_pDD->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
                hRet = m_pDD->SetDisplayMode(FScreen.Width, FScreen.Height, FScreen.Bpp,NULL,NULL);

        }
        else    hRet = m_pDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
        if(DDError(hRet != DD_OK,"DDSetCoop")) return(false);

        HRESULT hr;

        DDSURFACEDESC2 ddsd;
        ZeroMemory( &ddsd, sizeof( ddsd ) );
        ddsd.dwSize = sizeof( ddsd );
        ddsd.dwFlags = DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

        if(DDError(hr = m_pDD->CreateSurface(&ddsd, &m_pddsFrontBuffer, NULL)
                ,"CreateFrontSurface")) return(false);

        // Create the backbuffer surface
        ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
        ddsd.dwWidth = 1024;
        ddsd.dwHeight = 768;

        hr = m_pDD->CreateSurface(&ddsd, &m_pddsFrame, NULL);
        if (hr)
        {
                ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
                ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
                ddsd.dwWidth = 460;
                ddsd.dwHeight = 400;
                hr = m_pDD->CreateSurface(&ddsd, &m_pddsFrame, NULL);
                if(DDError(hr,"CreateBackSurface")) return(false);
                tv.DisableAdvanced=1;
        }

        if (!Form1->FullScreen)
        {
                if(DDError(hr = m_pDD->CreateClipper(0, &pcClipper, NULL)
                        ,"CreateClipper")) return(false);

                if(DDError(hr = pcClipper->SetHWnd(0, hWnd)
                        ,"SetClipperHwnd"))
                {
                        pcClipper->Release();
                        return(false);
                }


                if(DDError(hr = m_pddsFrontBuffer->SetClipper(pcClipper)
                        ,"SetClipperSurface"))
                {
                        pcClipper->Release();
                        return(false);
                }
        }

        return(true);
}