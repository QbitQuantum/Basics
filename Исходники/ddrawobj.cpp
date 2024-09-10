//
// CDDrawObject::Initialize(): Just creates a DDraw object.
//
BOOL CDDrawObject::Initialize(HWND hWndApp)
{
    DbgLog((LOG_TRACE, 5, TEXT("CDDrawObject::Initialize() entered"))) ;
    
    HRESULT hr = DirectDrawCreate(NULL, &m_pDDObject, NULL) ;
    if (FAILED(hr) || NULL == m_pDDObject)
    {
        MessageBox(hWndApp, 
            TEXT("Can't create a DirectDraw object.\nPress OK to end the app."), 
            TEXT("Error"), MB_OK | MB_ICONSTOP) ;
        return FALSE ;
    }
    
    return TRUE;
}