// CefJamCEFHtmlView message handlers
BOOL CefJamCEFHtmlView::CreateFromResource(UINT nID, CWnd* pParent,LPCTSTR csControlClass)
{
    CRect rc;

    CString csCompareClass=csControlClass;
    if (csCompareClass.CompareNoCase(HTMLVIEW_CONTROL_CLASS_CSTATIC)==0)
    {
        CStatic wndStatic;
        if (!wndStatic.SubclassDlgItem(nID, pParent))
            return FALSE;

        // Get static control rect, convert to parent's client coords.

        wndStatic.GetWindowRect(&rc);
        pParent->ScreenToClient(&rc);
        wndStatic.DestroyWindow();
    }
    else if (csCompareClass.CompareNoCase(HTMLVIEW_CONTROL_CLASS_CEDIT)==0)
    {
        CEdit wndEdit;
        if (!wndEdit.SubclassDlgItem(nID, pParent))
            return FALSE;

        // Get static control rect, convert to parent's client coords.

        wndEdit.GetWindowRect(&rc);
        pParent->ScreenToClient(&rc);
        wndEdit.DestroyWindow();
    }
    else
    {
        return FALSE;
    }

    // create HTML control (CHtmlView)
    return Create(NULL,						 // class name
                  NULL,										 // title
                  (WS_CHILD | WS_VISIBLE|WS_CLIPCHILDREN ),			 // style
                  rc,										 // rectangle
                  pParent,									 // parent
                  nID,										 // control ID
                  NULL);									 // frame/doc context not used
}