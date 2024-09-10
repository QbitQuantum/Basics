BOOL CInfoSheet::OnIdle(LONG lCount)
{
  // get active view 
  CWorldEditorView *pWorldEditorView = theApp.GetActiveView();
  // get active document 
  CWorldEditorDoc* pDoc = theApp.GetActiveDocument();
  
  // if we don't have view
  if( pDoc == NULL)
  {
    // force info mode: INFO_MODE_GLOBAL
    if( m_ModeID != INFO_MODE_GLOBAL)
    {
      SetInfoModeGlobal();
      CMainFrame* pMainFrame = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
      pMainFrame->SetFocus();
    }
  }
  else
  {
    // if CSG is on
    if( pDoc->m_iMode == CSG_MODE)
    {
      ASSERT(pDoc->m_pwoSecondLayer != NULL);
      // if CSG is done with primitive force info mode: INFO_MODE_PRIMITIVE
      if( pDoc->m_bPrimitiveMode)
      {
        if( m_ModeID != INFO_MODE_PRIMITIVE)
        {
          // primitive mode includes position page
          SetInfoModePrimitive();
        }
      }
      // else force info mode: INFO_MODE_POSITION
      else
      {
        if( m_ModeID != INFO_MODE_POSITION)
        {
          // no primitive page, only position page
          SetInfoModePosition();
        }
      }
    }
    // else if we are in entity mode and only one entity is selected,
    // force info mode: INFO_MODE_POSITION
    else if( (pDoc->m_iMode == ENTITY_MODE) && (pDoc->m_selEntitySelection.Count() == 1) )
    {
      if( m_ModeID != INFO_MODE_POSITION)
      {
        SetInfoModePosition();
      }
    }
    // else if we are in polygon mode
    else if( pDoc->m_iMode == POLYGON_MODE)
    {
      if( m_ModeID == INFO_MODE_POLYGON)
      {
        if( GetActivePage() == &m_PgTexture)    _iLastActivePgInPolygonMode = 1;
        else if( GetActivePage() == &m_PgShadow)_iLastActivePgInPolygonMode = 2;
        else                                    _iLastActivePgInPolygonMode = 3;
      }
      if( m_ModeID != INFO_MODE_POLYGON)
      {
        SetInfoModePolygon();
      }
    }
    // else if we are in sector mode
    else if( pDoc->m_iMode == SECTOR_MODE)
    {
      if( m_ModeID != INFO_MODE_SECTOR)
      {
        SetInfoModeSector();
      }
    }
    // else if we are in terrain mode
    else if( pDoc->m_iMode == TERRAIN_MODE)
    {
      if( m_ModeID != INFO_MODE_TERRAIN)
      {
        SetInfoModeTerrain();
      }      
    }
    // we are not in CSG mode nor in single entity mode, force info mode: INFO_MODE_GLOBAL
    else
    {
      if( m_ModeID != INFO_MODE_GLOBAL)
      {
        SetInfoModeGlobal();
      }
    }
  }
  // call OnIdle() for active page
  CPropertyPage *pgActivPage = GetActivePage();
  CALLACTIVEPAGE(OnIdle, lCount);
  return TRUE;
}