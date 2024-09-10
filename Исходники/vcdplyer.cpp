/******************************Public*Routine******************************\
* OpenMovie
*
\**************************************************************************/
HRESULT
CMovie::OpenMovie(
    TCHAR *lpFileName
    )
{
    IUnknown        *pUnk;
    HRESULT         hres;
    WCHAR           FileName[MAX_PATH];

    // Check input string
    if (lpFileName == NULL)
        return E_POINTER;

    hres = StringCchCopyW(FileName, NUMELMS(FileName), lpFileName);

    hres = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if(hres == S_FALSE)
        CoUninitialize();

    hres = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
                            IID_IUnknown, (LPVOID *)&pUnk);

    if(SUCCEEDED(hres))
    {
        m_Mode = MOVIE_OPENED;
        hres = pUnk->QueryInterface(IID_IFilterGraph, (LPVOID *)&m_Fg);
        if(FAILED(hres))
        {
            pUnk->Release();
            return hres;
        }

        hres = AddVideoMixingRendererToFG();
        if(FAILED(hres))
        {
            m_Fg->Release(); m_Fg = NULL;
            return hres;
        }

        hres = pUnk->QueryInterface(IID_IGraphBuilder, (LPVOID *)&m_Gb);
        if(FAILED(hres))
        {
            pUnk->Release();
            m_Fg->Release(); m_Fg = NULL;
            m_Wc->Release(); m_Wc = NULL;
            return hres;
        }

        hres = RenderFileToVideoRenderer( m_Gb, FileName, TRUE);
        if(FAILED(hres))
        {
            pUnk->Release();
            m_Fg->Release(); m_Fg = NULL;
            m_Wc->Release(); m_Wc = NULL;
            m_Gb->Release(); m_Gb = NULL;
            return hres;
        }

        hres = m_Wc->QueryInterface(IID_IVMRMixerControl9, (LPVOID *) &m_pMixControl);
        if(FAILED(hres))
        {
            pUnk->Release();
            m_Fg->Release(); m_Fg = NULL;
            m_Wc->Release(); m_Wc = NULL;
            m_Gb->Release(); m_Gb = NULL;
            m_pMixControl = NULL;
            return hres;
        }

        hres = pUnk->QueryInterface(IID_IMediaControl, (LPVOID *)&m_Mc);
        if(FAILED(hres))
        {
            pUnk->Release();
            m_Fg->Release(); m_Fg = NULL;
            m_Wc->Release(); m_Wc = NULL;
            m_Gb->Release(); m_Gb = NULL;
            return hres;
        }

        //
        // Not being able to get the IMediaEvent interface doesn't
        // necessarly mean that we can't play the graph.
        //
        pUnk->QueryInterface(IID_IMediaEvent, (LPVOID *)&m_Me);
        GetMovieEventHandle();

        pUnk->QueryInterface(IID_IMediaSeeking, (LPVOID *)&m_Ms);
        pUnk->Release();
        return S_OK;
    }
    else
    {
        m_Fg = NULL;
    }

    return hres;
}