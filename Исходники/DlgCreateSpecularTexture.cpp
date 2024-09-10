void CDlgCreateSpecularTexture::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

  if( !pDX->m_bSaveAndValidate)
  {
    INDEX iExponent = DEFAULT_EXPONENT_POS;
    if( IsWindow( m_sliderSpecularExponent.m_hWnd))
    {
      iExponent = m_sliderSpecularExponent.GetPos();
    }
    CTString strNumericalExponent;
    strNumericalExponent.PrintF( "Value: %.1f", GetFactorForPercentage(iExponent));
    m_strNumericalExponent = strNumericalExponent;
  }
	
  //{{AFX_DATA_MAP(CDlgCreateSpecularTexture)
	DDX_Control(pDX, IDC_SPECULAR_EXPONENT, m_sliderSpecularExponent);
	DDX_Control(pDX, IDC_SPECULAR_COLOR, m_colorSpecular);
	DDX_Control(pDX, IDC_SIZE_IN_PIXELS, m_comboSizeInPixels);
	DDX_Control(pDX, IDC_LIGHT_COLOR, m_colorLight);
	DDX_Control(pDX, IDC_AMBIENT_COLOR, m_colorAmbient);
	DDX_Text(pDX, IDC_NUMERIC_EXPONENT_T, m_strNumericalExponent);
	DDX_Check(pDX, IDC_AUTO_ROTATE, m_bAutoRotate);
	//}}AFX_DATA_MAP
  
  if( (pDX->m_bSaveAndValidate) && IsWindow( m_sliderSpecularExponent.m_hWnd) )
  {                    
    INDEX iSlider = m_sliderSpecularExponent.GetPos();
    CreateTexture( CTString("temp\\SpecularTemp.tex"), GetFactorForPercentage( iSlider));
    CTextureData *pTD = (CTextureData *) m_moModel.mo_toSpecular.GetData();
    if( pTD != NULL) pTD->Reload();
    Invalidate( FALSE);
  }
}