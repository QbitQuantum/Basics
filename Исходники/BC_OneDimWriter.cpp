void CBC_OneDimWriter::ShowBitmapChars(CFX_DIBitmap* pOutBitmap,
                                       const CFX_ByteString str,
                                       FX_FLOAT geWidth,
                                       FXTEXT_CHARPOS* pCharPos,
                                       FX_FLOAT locX,
                                       FX_FLOAT locY,
                                       int32_t barWidth) {
  int32_t iFontSize = (int32_t)fabs(m_fFontSize);
  int32_t iTextHeight = iFontSize + 1;
  CFX_FxgeDevice ge;
  ge.Create((int)geWidth, iTextHeight, m_colorSpace, nullptr);
  FX_RECT geRect(0, 0, (int)geWidth, iTextHeight);
  ge.FillRect(&geRect, m_backgroundColor);
  CFX_Matrix affine_matrix(1.0, 0.0, 0.0, -1.0, 0.0, (FX_FLOAT)iFontSize);
  ge.DrawNormalText(str.GetLength(), pCharPos, m_pFont, (FX_FLOAT)iFontSize,
                    &affine_matrix, m_fontColor, FXTEXT_CLEARTYPE);
  CFX_FxgeDevice geBitmap;
  geBitmap.Attach(pOutBitmap, false, nullptr, false);
  geBitmap.SetDIBits(ge.GetBitmap(), (int)locX, (int)locY);
}