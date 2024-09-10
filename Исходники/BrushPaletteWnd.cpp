void CBrushPaletteWnd::OnPaint() 
{
  {
  CPaintDC dc(this); // device context for painting
  }
  // skip if already drawing
  extern BOOL _bInTestGame; 
	if( _bInTestGame) return;

  if( m_iTimerID == -1)
  {
    m_iTimerID = (int) SetTimer( 1, 10, NULL);
  }

  POINT ptMouse;
  GetCursorPos( &ptMouse); 
  ScreenToClient( &ptMouse);

  // if there is a valid drawport, and the drawport can be locked
  if( m_pDrawPort != NULL ) {
    m_pDrawPort->SetAsCurrent();

    CWorldEditorView *pWorldEditorView = theApp.GetActiveView();
    ASSERT( pWorldEditorView != NULL);
    // clear background
    m_pDrawPort->Fill( C_lGRAY|CT_OPAQUE);
    // erase z-buffer
    m_pDrawPort->FillZBuffer(ZBUF_BACK);
    // for all brushes
    for( INDEX iBrush=0; iBrush<CT_BRUSHES; iBrush++)
    {
      // get current brush's box in pixels inside window
      PIXaabbox2D boxBrush = GetBrushBBox( iBrush);
      RenderBrushShape( iBrush, boxBrush, m_pDrawPort);

      TIME tm=_pTimer->GetRealTimeTick();
      // if we are drawing selected brush
      if(iBrush==theApp.m_fCurrentTerrainBrush)
      {
        m_pDrawPort->SetAsCurrent();
        FLOAT fFactor=sin(tm*8)/2.0f+0.5f;
        COLOR colSelected=LerpColor(C_lGRAY,C_RED,fFactor);
        m_pDrawPort->DrawBorder(boxBrush.Min()(1)-1, boxBrush.Min()(2)-1, 
                                boxBrush.Max()(1)-boxBrush.Min()(1)+2, boxBrush.Max()(2)-boxBrush.Min()(2)+2,
                                colSelected|CT_OPAQUE);
      }
      PIXaabbox2D boxPoint( PIX2D( ptMouse.x, ptMouse.y), PIX2D(ptMouse.x, ptMouse.y) );
      if( (boxBrush & boxPoint) == boxPoint)
      {
        m_pDrawPort->SetAsCurrent();
        INDEX iRot=((ULONG)(tm*25.0f))&7;
        ULONG ulLineType=0x0f0f0f0f<<iRot;
        m_pDrawPort->DrawBorder(boxBrush.Min()(1)-1, boxBrush.Min()(2)-1, 
                                boxBrush.Max()(1)-boxBrush.Min()(1)+2, boxBrush.Max()(2)-boxBrush.Min()(2)+2,
                                C_BLUE|CT_OPAQUE, ulLineType);
      }
    }

    // if there is a valid viewport
    if (m_pViewPort!=NULL)
    {
      m_pViewPort->SwapBuffers();
    }
  }
}