void CDlgCreateNormalTexture::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
  // if texture preview windows are not yet created
  if( !m_bPreviewWindowsCreated)
  {
    // ---------------- Create custom window that will show how created texture will look like
    CWnd *pWndCreatedTexturePreview = GetDlgItem(IDC_TEXTURE_PREVIEW_WINDOW);
    ASSERT(pWndCreatedTexturePreview != NULL);
    CRect rectPreviewCreatedTextureWnd;
    // get rectangle occupied by preview texture window
    pWndCreatedTexturePreview->GetWindowRect( &rectPreviewCreatedTextureWnd);
    ScreenToClient( &rectPreviewCreatedTextureWnd);
    // create window for for showing created texture
    m_wndViewCreatedTexture.Create( NULL, NULL, WS_BORDER|WS_VISIBLE, rectPreviewCreatedTextureWnd,
                                    this, IDW_VIEW_CREATED_TEXTURE);
    // mark that custom windows are created
    m_bPreviewWindowsCreated = TRUE;
  }
}