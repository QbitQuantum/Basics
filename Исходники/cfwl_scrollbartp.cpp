void CFWL_ScrollBarTP::DrawPaw(CFX_Graphics* pGraphics,
                               const CFX_RectF* pRect,
                               FX_BOOL bVert,
                               FWLTHEME_STATE eState,
                               CFX_Matrix* pMatrix) {
  CFX_Path path;
  path.Create();
  if (bVert) {
    FX_FLOAT fPawLen = kPawLength;
    if (pRect->width / 2 <= fPawLen) {
      fPawLen = (pRect->width - 6) / 2;
    }
    FX_FLOAT fX = pRect->left + pRect->width / 4;
    FX_FLOAT fY = pRect->top + pRect->height / 2;
    path.MoveTo(fX, fY - 4);
    path.LineTo(fX + fPawLen, fY - 4);
    path.MoveTo(fX, fY - 2);
    path.LineTo(fX + fPawLen, fY - 2);
    path.MoveTo(fX, fY);
    path.LineTo(fX + fPawLen, fY);
    path.MoveTo(fX, fY + 2);
    path.LineTo(fX + fPawLen, fY + 2);
    CFX_Color clrLight(m_pThemeData->clrPawColorLight[eState - 1]);
    pGraphics->SetLineWidth(1);
    pGraphics->SetStrokeColor(&clrLight);
    pGraphics->StrokePath(&path);
    fX++;
    path.Clear();
    path.MoveTo(fX, fY - 3);
    path.LineTo(fX + fPawLen, fY - 3);
    path.MoveTo(fX, fY - 1);
    path.LineTo(fX + fPawLen, fY - 1);
    path.MoveTo(fX, fY + 1);
    path.LineTo(fX + fPawLen, fY + 1);
    path.MoveTo(fX, fY + 3);
    path.LineTo(fX + fPawLen, fY + 3);
    CFX_Color clrDark(m_pThemeData->clrPawColorDark[eState - 1]);
    pGraphics->SetLineWidth(1);
    pGraphics->SetStrokeColor(&clrDark);
    pGraphics->StrokePath(&path, pMatrix);
  } else {
    FX_FLOAT fPawLen = kPawLength;
    if (pRect->height / 2 <= fPawLen) {
      fPawLen = (pRect->height - 6) / 2;
    }
    FX_FLOAT fX = pRect->left + pRect->width / 2;
    FX_FLOAT fY = pRect->top + pRect->height / 4;
    path.MoveTo(fX - 4, fY);
    path.LineTo(fX - 4, fY + fPawLen);
    path.MoveTo(fX - 2, fY);
    path.LineTo(fX - 2, fY + fPawLen);
    path.MoveTo(fX, fY);
    path.LineTo(fX, fY + fPawLen);
    path.MoveTo(fX + 2, fY);
    path.LineTo(fX + 2, fY + fPawLen);
    CFX_Color clrLight(m_pThemeData->clrPawColorLight[eState - 1]);
    pGraphics->SetLineWidth(1);
    pGraphics->SetStrokeColor(&clrLight);
    pGraphics->StrokePath(&path, pMatrix);
    fY++;
    path.Clear();
    path.MoveTo(fX - 3, fY);
    path.LineTo(fX - 3, fY + fPawLen);
    path.MoveTo(fX - 1, fY);
    path.LineTo(fX - 1, fY + fPawLen);
    path.MoveTo(fX + 1, fY);
    path.LineTo(fX + 1, fY + fPawLen);
    path.MoveTo(fX + 3, fY);
    path.LineTo(fX + 3, fY + fPawLen);
    CFX_Color clrDark(m_pThemeData->clrPawColorDark[eState - 1]);
    pGraphics->SetLineWidth(1);
    pGraphics->SetStrokeColor(&clrDark);
    pGraphics->StrokePath(&path, pMatrix);
  }
}