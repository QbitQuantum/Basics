///////////////////////////////////////////////////////////////////////////////
// Descripcion:
// - Crea la fuente true type, pero NO la selecciona. 
// Parametros:
// - hdc. DC a la superficie sobre la que se va a crear la fuente.
// - swDeciPt. Tamaño de la fuentes en puntos por 10. Si nuestra fuente va a
//   tener un tamaño de 16, debera de valer 16x10 = 160.
// Devuelve:
// Notas:
///////////////////////////////////////////////////////////////////////////////
void 
CFont::CreateTTFont(const HDC& hdc, const sword& swDeciPt)
{
  // SOLO si los parametros son validos
  ASSERT(hdc);
  ASSERT(swDeciPt);

  // Configura el DC recibido  
  SetGraphicsMode(hdc, GM_ADVANCED);
  ModifyWorldTransform(hdc, NULL, MWT_IDENTITY);
  SetViewportOrgEx(hdc, 0, 0, NULL);
  SetWindowOrgEx(hdc, 0, 0, NULL);

  // Se establece la res. logica
  float cxDpi = (float) GetDeviceCaps(hdc, LOGPIXELSX);
  float cyDpi = (float) GetDeviceCaps(hdc, LOGPIXELSY);

  // Define ptos. por pulgada
  POINT pt;
  pt.x = 0;
  pt.y = (sword) (swDeciPt * cyDpi / 72);
  DPtoLP(hdc, &pt, 1);

  // Configura y crea la fuente
  LOGFONT lf;
  memset(&lf, 0, sizeof(lf));
  lf.lfHeight = -(sword) (fabs(pt.y) / 10.0 + 0.5);
  strcpy(lf.lfFaceName, m_FontInfo.szName.c_str());
  m_FontInfo.hFont = CreateFontIndirect(&lf);
  lf.lfQuality = ANTIALIASED_QUALITY;

  // Se obtiene datos sobre metrica y anchura
  m_FontInfo.hPrevFont = (HFONT) SelectObject(hdc, m_FontInfo.hFont);
  GetTextMetrics(hdc, &m_FontInfo.tm);
  GetCharABCWidths(hdc, 32, 255, m_FontInfo.abc);

  // Restaura el estado del hdc anterior  
}