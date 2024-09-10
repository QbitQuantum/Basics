void CFWL_WidgetTP::Draw3DRect(CFX_Graphics* pGraphics,
                               FWLTHEME_EDGE eType,
                               FX_FLOAT fWidth,
                               const CFX_RectF* pRect,
                               FX_ARGB cr1,
                               FX_ARGB cr2,
                               FX_ARGB cr3,
                               FX_ARGB cr4,
                               CFX_Matrix* pMatrix) {
  if (!pGraphics)
    return;
  if (!pRect)
    return;
  pGraphics->SaveGraphState();
  if (eType == FWLTHEME_EDGE_Flat) {
    CFX_Path path;
    path.Create();
    path.AddRectangle(pRect->left, pRect->top, pRect->width, pRect->height);
    path.AddRectangle(pRect->left + 1, pRect->top + 1, pRect->width - 2,
                      pRect->height - 2);
    CFX_Color cr(ArgbEncode(255, 100, 100, 100));
    pGraphics->SetFillColor(&cr);
    pGraphics->FillPath(&path, FXFILL_WINDING, pMatrix);
    path.Clear();
    path.AddRectangle(pRect->left + 1, pRect->top + 1, pRect->width - 2,
                      pRect->height - 2);
    path.AddRectangle(pRect->left + 2, pRect->top + 2, pRect->width - 4,
                      pRect->height - 4);
    cr.Set(0xFFFFFFFF);
    pGraphics->SetFillColor(&cr);
    pGraphics->FillPath(&path, FXFILL_WINDING, pMatrix);
  } else {
    FX_FLOAT fLeft = pRect->left;
    FX_FLOAT fRight = pRect->right();
    FX_FLOAT fTop = pRect->top;
    FX_FLOAT fBottom = pRect->bottom();
    FX_FLOAT fHalfWidth = fWidth / 2.0f;
    CFX_Color crLT(eType == FWLTHEME_EDGE_Raised ? cr4 : cr1);
    pGraphics->SetFillColor(&crLT);
    CFX_Path pathLT;
    pathLT.Create();
    pathLT.MoveTo(fLeft, fBottom - fHalfWidth);
    pathLT.LineTo(fLeft, fTop);
    pathLT.LineTo(fRight - fHalfWidth, fTop);
    pathLT.LineTo(fRight - fHalfWidth, fTop + fHalfWidth);
    pathLT.LineTo(fLeft + fHalfWidth, fTop + fHalfWidth);
    pathLT.LineTo(fLeft + fHalfWidth, fBottom - fHalfWidth);
    pathLT.LineTo(fLeft, fBottom - fHalfWidth);
    pGraphics->FillPath(&pathLT, FXFILL_WINDING, pMatrix);
    crLT = CFX_Color(eType == FWLTHEME_EDGE_Raised ? cr3 : cr2);
    pGraphics->SetFillColor(&crLT);
    pathLT.Clear();
    pathLT.MoveTo(fLeft + fHalfWidth, fBottom - fWidth);
    pathLT.LineTo(fLeft + fHalfWidth, fTop + fHalfWidth);
    pathLT.LineTo(fRight - fWidth, fTop + fHalfWidth);
    pathLT.LineTo(fRight - fWidth, fTop + fWidth);
    pathLT.LineTo(fLeft + fWidth, fTop + fWidth);
    pathLT.LineTo(fLeft + fWidth, fBottom - fWidth);
    pathLT.LineTo(fLeft + fHalfWidth, fBottom - fWidth);
    pGraphics->FillPath(&pathLT, FXFILL_WINDING, pMatrix);
    CFX_Color crRB(eType == FWLTHEME_EDGE_Raised ? cr1 : cr3);
    pGraphics->SetFillColor(&crRB);
    CFX_Path pathRB;
    pathRB.Create();
    pathRB.MoveTo(fRight - fHalfWidth, fTop + fHalfWidth);
    pathRB.LineTo(fRight - fHalfWidth, fBottom - fHalfWidth);
    pathRB.LineTo(fLeft + fHalfWidth, fBottom - fHalfWidth);
    pathRB.LineTo(fLeft + fHalfWidth, fBottom - fWidth);
    pathRB.LineTo(fRight - fWidth, fBottom - fWidth);
    pathRB.LineTo(fRight - fWidth, fTop + fHalfWidth);
    pathRB.LineTo(fRight - fHalfWidth, fTop + fHalfWidth);
    pGraphics->FillPath(&pathRB, FXFILL_WINDING, pMatrix);
    crRB = CFX_Color(eType == FWLTHEME_EDGE_Raised ? cr2 : cr4);
    pGraphics->SetFillColor(&crRB);
    pathRB.Clear();
    pathRB.MoveTo(fRight, fTop);
    pathRB.LineTo(fRight, fBottom);
    pathRB.LineTo(fLeft, fBottom);
    pathRB.LineTo(fLeft, fBottom - fHalfWidth);
    pathRB.LineTo(fRight - fHalfWidth, fBottom - fHalfWidth);
    pathRB.LineTo(fRight - fHalfWidth, fTop);
    pathRB.LineTo(fRight, fTop);
    pGraphics->FillPath(&pathRB, FXFILL_WINDING, pMatrix);
  }
  pGraphics->RestoreGraphState();
}