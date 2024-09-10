/*
 * CSite::ObjectInitialize
 * (Protected)
 *
 * Purpose:
 *  Performs operations necessary after creating an object or
 *  reloading one from storage.
 *
 * Parameters:
 *	pchPath			The path that we want to load from
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */
BOOL CSite::ObjectInitialize(LPCTSTR pchPath)
{
    HRESULT         hr;
    DWORD           dw;

    if ( NULL == m_pObj )
    {
        ASSERT(FALSE);
        return FALSE;
    }


    //We need an IOleObject most of the time, so get one here.
    hr = m_pObj->QueryInterface( IID_IOleObject, (void **)&m_pIOleObject );
    if ( FAILED( hr ) )
    {
        ASSERT(FALSE);
        return FALSE;
    }
    //SetClientSite is critical for DocObjects
    hr = m_pIOleObject->SetClientSite( m_pImpIOleClientSite );
    if(FAILED(hr))
    {
        ASSERT(FALSE);
    }

    hr = m_pIOleObject->Advise( m_pImpIAdviseSink, &dw );
    if(FAILED(hr))
    {
        ASSERT(FALSE);
    }

    if ( FAILED( Load( pchPath ) ) )
    {
        ASSERT(FALSE);
        return FALSE;
    }


    // Put the object in the running state
    hr = OleRun( m_pIOleObject );
    if(FAILED(hr))
    {
        ASSERT(FALSE);
    }
    return TRUE;
}