CDlgSelectMode::CDlgSelectMode( CDisplayMode &dm, enum GfxAPIType &gfxAPI, 
                                CWnd* pParent /*=NULL*/) : CDialog( CDlgSelectMode::IDD, pParent)
{
  // obtain all available modes
  m_pdmAvailableModes = _pGfx->EnumDisplayModes(m_ctAvailableDisplayModes);

  // remember initial mode reference
  m_pdm = &dm;
  m_pGfxAPI = &gfxAPI;

  //{{AFX_DATA_INIT(CDlgSelectMode)
	m_strCurrentMode = _T("");
	m_strCurrentDriver = _T("");
	m_iColor = -1;
	//}}AFX_DATA_INIT

  // set current mode and driver strings
  CTString str;
  str.PrintF( "%d x %d x %s", dm.dm_pixSizeI, dm.dm_pixSizeJ, dm.DepthString());
  m_strCurrentMode = str;

  switch(gfxAPI) {
  case GAT_OGL:
    m_strCurrentDriver = "OpenGL";
    break;
#ifdef SE1_D3D
  case GAT_D3D:
    m_strCurrentDriver = "Direct3D";
    break;
#endif // SE1_D3D
  default:
    m_strCurrentDriver = "none";
    break;
  }
}