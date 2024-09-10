//-----------------------------------------------------------------------------
// Does:   Open a Resource And Load It Into IPicture (Interface)
// ~~~~    (.BMP .DIB .EMF .GIF .ICO .JPG .WMF)
//
// Note:   When Adding a Bitmap Resource It Would Automatically Show On "Bitmap"
// ~~~~    This NOT Good Coz We Need To Load It From a Custom Resource "BMP"
//         To Add a Custom Rresource: Import Resource -> Open As -> Custom
//         (Both .BMP And .DIB Should Be Found Under "BMP")
//
// InPut:  ResourceName - As a UINT Defined (Example: IDR_PICTURE_RESOURCE)
// ~~~~~   ResourceType - Type Name (Example: "JPG")
//
// OutPut: TRUE If Succeeded...
// ~~~~~~
//-----------------------------------------------------------------------------
BOOL CPicViewer::Load(UINT ResourceName, LPCSTR ResourceType)
//=============================================================================
{
    BOOL bResult = FALSE;
    
    HGLOBAL		hGlobal = NULL;
    HRSRC		hSource = NULL;
    LPVOID		lpVoid  = NULL;
    int			nSize   = 0;
    
    if(m_IPicture != NULL) FreePictureData(); // Important - Avoid Leaks...
    
    hSource = FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(ResourceName), ResourceType);
    
    if(hSource == NULL)
    {
        TRACE( "FindResource() Failed\n" );
        // 		HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
        // 		MessageBoxEx(hWnd, "FindResource() Failed\t", ERROR_TITLE, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
        return(FALSE);
    }
    
    hGlobal = LoadResource(AfxGetResourceHandle(), hSource);
    if(hGlobal == NULL)
    {
        TRACE( "LoadResource() Failed\n" );
        // 		HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
        // 		MessageBoxEx(hWnd, "LoadResource() Failed\t", ERROR_TITLE, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
        return(FALSE);
    }
    
    lpVoid = LockResource(hGlobal);
    if(lpVoid == NULL)
    {
        TRACE( "LockResource() Failed\n" );
        // 		HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
        // 		MessageBoxEx(hWnd, "LockResource() Failed\t", ERROR_TITLE, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
        return(FALSE);
    }
    
    nSize = (UINT)SizeofResource(AfxGetResourceHandle(), hSource);
    if(LoadPictureData((BYTE*)hGlobal, nSize)) bResult = TRUE;
    
    UnlockResource(hGlobal); // 16Bit Windows Needs This
    FreeResource(hGlobal); // 16Bit Windows Needs This (32Bit - Automatic Release)
    
    m_Weight = nSize; // Update Picture Size Info...
    
    if(m_IPicture != NULL) // Do Not Try To Read From Memory That Is Not Exist...
    { 
        m_IPicture->get_Height(&m_Height);
        m_IPicture->get_Width(&m_Width);
        // Calculate Its Size On a "Standard" (96 DPI) Device Context
        m_Height = MulDiv(m_Height, 96, HIMETRIC_INCH);
        m_Width  = MulDiv(m_Width,  96, HIMETRIC_INCH);
    }
    else // Picture Data Is Not a Known Picture Type
    {
        m_Height = 0;
        m_Width = 0;
        bResult = FALSE;
    }
    
    return(bResult);
}