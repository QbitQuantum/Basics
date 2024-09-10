STDMETHODIMP 
IMemStream::Stat( 
    STATSTG *pstatstg,
    DWORD grfStatFlag )
{
    #if 0        
    if( grfStatFlag & STATFLAG_DEFAULT ) // wants the stream name using CoMemTaskAlloc
    {
        pstatstg->pwcsName = (PTCHAR) CoTaskMemAlloc( 5 ); //  STATFLAG_NONAME
        _tcscpy( pstatstg->pwcsName, _T("Test") );
    }
    #endif
    memset( pstatstg, 0, sizeof(STATSTG) );
    pstatstg->type = STGTY_STREAM;
    pstatstg->cbSize.QuadPart = m_ullEnd;
    pstatstg->grfMode = STGM_SIMPLE|STGM_READ; //0x80000000;
    pstatstg->clsid = IID_IStream;

    // ??? don't know what to do here...
    FILETIME ft;
    CoFileTimeNow( &ft );
    pstatstg->mtime = ft;
    pstatstg->ctime = ft;
    pstatstg->atime = ft;

    return S_OK;
}