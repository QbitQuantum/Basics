void CBC_OnedUPCAWriter::ShowChars(const CFX_WideStringC& contents,
                                   CFX_DIBitmap* pOutBitmap,
                                   CFX_RenderDevice* device,
                                   const CFX_Matrix* matrix,
                                   int32_t barWidth,
                                   int32_t multiple,
                                   int32_t& e) {
  if (!device && !pOutBitmap) {
    e = BCExceptionIllegalArgument;
    return;
  }

  int32_t leftPadding = 7 * multiple;
  int32_t leftPosition = 10 * multiple + leftPadding;
  CFX_ByteString str = FX_UTF8Encode(contents);
  int32_t iLen = str.GetLength();
  FXTEXT_CHARPOS* pCharPos = FX_Alloc(FXTEXT_CHARPOS, iLen);
  FXSYS_memset(pCharPos, 0, sizeof(FXTEXT_CHARPOS) * iLen);
  CFX_ByteString tempStr = str.Mid(1, 5);
  FX_FLOAT strWidth = (FX_FLOAT)35 * multiple;
  FX_FLOAT blank = 0.0;
  CFX_FxgeDevice geBitmap;
  if (pOutBitmap)
    geBitmap.Attach(pOutBitmap, false, nullptr, false);

  iLen = tempStr.GetLength();
  int32_t iFontSize = (int32_t)fabs(m_fFontSize);
  int32_t iTextHeight = iFontSize + 1;
  if (!pOutBitmap) {
    CFX_Matrix matr(m_outputHScale, 0.0, 0.0, 1.0, 0.0, 0.0);
    CFX_FloatRect rect(
        (FX_FLOAT)leftPosition, (FX_FLOAT)(m_Height - iTextHeight),
        (FX_FLOAT)(leftPosition + strWidth - 0.5), (FX_FLOAT)m_Height);
    matr.Concat(*matrix);
    matr.TransformRect(rect);
    FX_RECT re = rect.GetOutterRect();
    device->FillRect(&re, m_backgroundColor);
    CFX_Matrix matr1(m_outputHScale, 0.0, 0.0, 1.0, 0.0, 0.0);
    CFX_FloatRect rect1(
        (FX_FLOAT)(leftPosition + 40 * multiple),
        (FX_FLOAT)(m_Height - iTextHeight),
        (FX_FLOAT)((leftPosition + 40 * multiple) + strWidth - 0.5),
        (FX_FLOAT)m_Height);
    matr1.Concat(*matrix);
    matr1.TransformRect(rect1);
    re = rect1.GetOutterRect();
    device->FillRect(&re, m_backgroundColor);
    FX_FLOAT strWidth1 = (FX_FLOAT)multiple * 7;
    CFX_Matrix matr2(m_outputHScale, 0.0, 0.0, 1.0, 0.0, 0.0);
    CFX_FloatRect rect2(0.0, (FX_FLOAT)(m_Height - iTextHeight),
                        (FX_FLOAT)strWidth1 - 1, (FX_FLOAT)m_Height);
    matr2.Concat(*matrix);
    matr2.TransformRect(rect2);
    re = rect2.GetOutterRect();
    device->FillRect(&re, m_backgroundColor);
    CFX_Matrix matr3(m_outputHScale, 0.0, 0.0, 1.0, 0.0, 0.0);
    CFX_FloatRect rect3(
        (FX_FLOAT)(leftPosition + 85 * multiple),
        (FX_FLOAT)(m_Height - iTextHeight),
        (FX_FLOAT)((leftPosition + 85 * multiple) + strWidth1 - 0.5),
        (FX_FLOAT)m_Height);
    matr3.Concat(*matrix);
    matr3.TransformRect(rect3);
    re = rect3.GetOutterRect();
    device->FillRect(&re, m_backgroundColor);
  }
  if (!pOutBitmap)
    strWidth = strWidth * m_outputHScale;

  CalcTextInfo(tempStr, pCharPos + 1, m_pFont, strWidth, iFontSize, blank);
  CFX_Matrix affine_matrix(1.0, 0.0, 0.0, -1.0, 0.0, (FX_FLOAT)iFontSize);
  CFX_FxgeDevice ge;
  if (pOutBitmap) {
    ge.Create((int)strWidth, iTextHeight, FXDIB_Argb, nullptr);
    ge.GetBitmap()->Clear(m_backgroundColor);
    ge.DrawNormalText(iLen, pCharPos + 1, m_pFont,
                      CFX_GEModule::Get()->GetFontCache(), (FX_FLOAT)iFontSize,
                      &affine_matrix, m_fontColor, FXTEXT_CLEARTYPE);
    geBitmap.SetDIBits(ge.GetBitmap(), leftPosition, m_Height - iTextHeight);
  } else {
    CFX_Matrix affine_matrix1(1.0, 0.0, 0.0, -1.0,
                              (FX_FLOAT)leftPosition * m_outputHScale,
                              (FX_FLOAT)(m_Height - iTextHeight + iFontSize));
    if (matrix) {
      affine_matrix1.Concat(*matrix);
    }
    device->DrawNormalText(
        iLen, pCharPos + 1, m_pFont, CFX_GEModule::Get()->GetFontCache(),
        (FX_FLOAT)iFontSize, &affine_matrix1, m_fontColor, FXTEXT_CLEARTYPE);
  }
  tempStr = str.Mid(6, 5);
  iLen = tempStr.GetLength();
  CalcTextInfo(tempStr, pCharPos + 6, m_pFont, strWidth, iFontSize, blank);
  if (pOutBitmap) {
    FX_RECT rect2(0, 0, (int)strWidth, iTextHeight);
    ge.FillRect(&rect2, m_backgroundColor);
    ge.DrawNormalText(iLen, pCharPos + 6, m_pFont,
                      CFX_GEModule::Get()->GetFontCache(), (FX_FLOAT)iFontSize,
                      &affine_matrix, m_fontColor, FXTEXT_CLEARTYPE);
    geBitmap.SetDIBits(ge.GetBitmap(), leftPosition + 40 * multiple,
                       m_Height - iTextHeight);
  } else {
    CFX_Matrix affine_matrix1(
        1.0, 0.0, 0.0, -1.0,
        (FX_FLOAT)(leftPosition + 40 * multiple) * m_outputHScale,
        (FX_FLOAT)(m_Height - iTextHeight + iFontSize));
    if (matrix) {
      affine_matrix1.Concat(*matrix);
    }
    device->DrawNormalText(
        iLen, pCharPos + 6, m_pFont, CFX_GEModule::Get()->GetFontCache(),
        (FX_FLOAT)iFontSize, &affine_matrix1, m_fontColor, FXTEXT_CLEARTYPE);
  }
  tempStr = str.Mid(0, 1);
  iLen = tempStr.GetLength();
  strWidth = (FX_FLOAT)multiple * 7;
  if (!pOutBitmap)
    strWidth = strWidth * m_outputHScale;

  CalcTextInfo(tempStr, pCharPos, m_pFont, strWidth, iFontSize, blank);
  if (pOutBitmap) {
    delete ge.GetBitmap();
    ge.Create((int)strWidth, iTextHeight, FXDIB_Argb, nullptr);
    ge.GetBitmap()->Clear(m_backgroundColor);
    ge.DrawNormalText(iLen, pCharPos, m_pFont,
                      CFX_GEModule::Get()->GetFontCache(), (FX_FLOAT)iFontSize,
                      &affine_matrix, m_fontColor, FXTEXT_CLEARTYPE);
    geBitmap.SetDIBits(ge.GetBitmap(), 0, m_Height - iTextHeight);
  } else {
    CFX_Matrix affine_matrix1(1.0, 0.0, 0.0, -1.0, 0,
                              (FX_FLOAT)(m_Height - iTextHeight + iFontSize));
    if (matrix) {
      affine_matrix1.Concat(*matrix);
    }
    device->DrawNormalText(
        iLen, pCharPos, m_pFont, CFX_GEModule::Get()->GetFontCache(),
        (FX_FLOAT)iFontSize, &affine_matrix1, m_fontColor, FXTEXT_CLEARTYPE);
  }
  tempStr = str.Mid(11, 1);
  iLen = tempStr.GetLength();
  CalcTextInfo(tempStr, pCharPos + 11, m_pFont, strWidth, iFontSize, blank);
  if (pOutBitmap) {
    delete ge.GetBitmap();
    ge.Create((int)strWidth, iTextHeight, FXDIB_Argb, nullptr);
    ge.GetBitmap()->Clear(m_backgroundColor);
    ge.DrawNormalText(iLen, pCharPos + 11, m_pFont,
                      CFX_GEModule::Get()->GetFontCache(), (FX_FLOAT)iFontSize,
                      &affine_matrix, m_fontColor, FXTEXT_CLEARTYPE);
    geBitmap.SetDIBits(ge.GetBitmap(), leftPosition + 85 * multiple,
                       m_Height - iTextHeight);
  } else {
    CFX_Matrix affine_matrix1(
        1.0, 0.0, 0.0, -1.0,
        (FX_FLOAT)(leftPosition + 85 * multiple) * m_outputHScale,
        (FX_FLOAT)(m_Height - iTextHeight + iFontSize));
    if (matrix) {
      affine_matrix1.Concat(*matrix);
    }
    device->DrawNormalText(
        iLen, pCharPos + 11, m_pFont, CFX_GEModule::Get()->GetFontCache(),
        (FX_FLOAT)iFontSize, &affine_matrix1, m_fontColor, FXTEXT_CLEARTYPE);
  }
  FX_Free(pCharPos);
}