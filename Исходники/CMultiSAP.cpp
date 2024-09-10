//-------------------------------------------------------------------------
//  SetFocus
//  add sound management here
//-------------------------------------------------------------------------
void CMultiSAP::SetFocus()
{
    CMovie *pmovie = m_movieList.GetSelectedMovie();

    if(pmovie && pmovie->m_Fg)
    {
        // Tell the resource manager that we are being made active.  This
        // will then cause the sound to switch to THE SELECTED MEDIA SOURCE.
        // This is especially
        // important when playing audio only files as there is no other
        // playback window.
        IResourceManager* pResourceManager;

        HRESULT hr = pmovie->m_Fg->QueryInterface(IID_IResourceManager,
                                                 (void**)&pResourceManager);

        if(SUCCEEDED(hr))
        {
            IUnknown* pUnknown;

            hr = pmovie->m_Fg->QueryInterface(IID_IUnknown, (void**)&pUnknown);

            if(SUCCEEDED(hr))
            {
                pResourceManager->SetFocus(pUnknown);
                pUnknown->Release();
            }

            pResourceManager->Release();
        }
    }
}