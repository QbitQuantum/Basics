//--------------------------------------------------------------------------------------
HRESULT CRatingsDB::LoadDB()
{
    // Find resource will pick the right ID_GDF_XML_STR based on the current language
    HRSRC hrsrc = FindResource( nullptr, MAKEINTRESOURCE(ID_RATINGS_XML), L"DATA" ); 
    if( hrsrc ) 
    { 
        HGLOBAL hgResource = LoadResource( nullptr, hrsrc ); 
        if( hgResource ) 
        { 
            BYTE* pResourceBuffer = (BYTE*)LockResource( hgResource ); 
            if( pResourceBuffer ) 
            { 
                DWORD dwGDFXMLSize = SizeofResource( nullptr, hrsrc );
                if( dwGDFXMLSize )
                {
                    // HGLOBAL from LoadResource() needs to be copied for CreateStreamOnHGlobal() to work
                    HGLOBAL hgResourceCopy = GlobalAlloc( GMEM_MOVEABLE, dwGDFXMLSize );
                    if( hgResourceCopy )
                    {
                        LPVOID pCopy = GlobalLock( hgResourceCopy );
                        if( pCopy )
                        {
                            CopyMemory( pCopy, pResourceBuffer, dwGDFXMLSize );
                            GlobalUnlock( hgResource );

                            IStream* piStream = nullptr;
                            HRESULT hr = CreateStreamOnHGlobal( hgResourceCopy, TRUE, &piStream ); 
                            if( SUCCEEDED(hr) && piStream )
                            {
                                IXMLDOMDocument *pDoc = nullptr;

                                // Load the XML into a IXMLDOMDocument object
                                hr = CoCreateInstance( CLSID_DOMDocument, nullptr, CLSCTX_INPROC_SERVER, 
                                                       IID_IXMLDOMDocument, (void**)&pDoc );
                                if( SUCCEEDED(hr) ) 
                                {
                                    IPersistStreamInit* pPersistStreamInit = nullptr;
                                    hr = pDoc->QueryInterface( IID_IPersistStreamInit, (void**) &pPersistStreamInit );
                                    if( SUCCEEDED(hr) ) 
                                    {
                                        hr = pPersistStreamInit->Load( piStream );
                                        if( SUCCEEDED(hr) ) 
                                        {
                                            // Get the root node to the XML doc and store it 
                                            pDoc->QueryInterface( IID_IXMLDOMNode, (void**)&m_pRootNode );
                                        }
                                        SAFE_RELEASE( pPersistStreamInit );
                                    }
                                    SAFE_RELEASE( pDoc );
                                }
                                SAFE_RELEASE( piStream );
                            }
                        }
                        GlobalFree( hgResourceCopy );
                    }
                }
            } 
        } 
    } 

    if( m_pRootNode )
        return S_OK;
    else
        return E_FAIL;
}