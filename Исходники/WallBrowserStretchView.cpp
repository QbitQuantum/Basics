/*
	CWallBrowserStretchView()
*/
CWallBrowserStretchView::CWallBrowserStretchView()
{
	m_pWinAppEx = (CWinAppEx*)AfxGetApp();
	m_bLoaded = FALSE;
	m_bHavePicture = FALSE;
	memset(m_szFileName,'\0',sizeof(m_szFileName));
	m_nViewType = m_pWinAppEx->m_Config.GetNumber(WALLBROWSER_OPTIONS_KEY,WALLBROWSER_VIEWTYPE_KEY);
	if(m_nViewType==VIEWTYPE_SCROLL)
	{
		// modalita' visualizzazione (centrato/isotropic)
		SetCenterMode(TRUE);
		SetMapMode(MM_ANISOTROPIC);
		SetCursorZoomMode(CURSOR_MODE_BYCLICK);
	}
	else if(m_nViewType==VIEWTYPE_STRETCH)
	{
		// modalita' visualizzazione (centrato/text)
		SetCenterMode(FALSE);
		SetMapMode(MM_TEXT);
		SetCursorZoomMode(CURSOR_MODE_NONE);
	}
	m_nDrawMode = m_pWinAppEx->m_Config.GetNumber(WALLBROWSER_OPTIONS_KEY,WALLBROWSER_DRAWMODE_KEY);
	m_rcInvalid.SetRect(-1,-1,-1,-1);
	m_rcClient.SetRect(-1,-1,-1,-1);
	m_ImageOperation.SetImage(NULL);
	m_ImageDraw.SetImage(NULL);
	m_bRebuildPalette = FALSE; // mettere a TRUE con le operazioni che cambiano l'immagine (ad es. grayscale)
	memset(m_szStatus,'\0',sizeof(m_szStatus));
	m_pMainFrameStatusBar = NULL;
	m_nUndoLevel = 0;
	m_nRedoLevel = 0;
	m_nLastOperation = -1;
	m_nRedo = -1;
}