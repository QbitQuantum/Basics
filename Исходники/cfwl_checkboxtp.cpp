void CFWL_CheckBoxTP::DrawSignDiamond(CFX_Graphics* pGraphics,
                                      const CFX_RectF* pRtSign,
                                      FX_ARGB argbFill,
                                      CFX_Matrix* pMatrix) {
  CFX_Path path;
  path.Create();
  FX_FLOAT fWidth = pRtSign->width;
  FX_FLOAT fHeight = pRtSign->height;
  FX_FLOAT fBottom = pRtSign->bottom();
  path.MoveTo(pRtSign->left + fWidth / 2, pRtSign->top);
  path.LineTo(pRtSign->left, pRtSign->top + fHeight / 2);
  path.LineTo(pRtSign->left + fWidth / 2, fBottom);
  path.LineTo(pRtSign->right(), pRtSign->top + fHeight / 2);
  path.LineTo(pRtSign->left + fWidth / 2, pRtSign->top);
  CFX_Color crFill(argbFill);
  pGraphics->SaveGraphState();
  pGraphics->SetFillColor(&crFill);
  pGraphics->FillPath(&path, FXFILL_WINDING, pMatrix);
  pGraphics->RestoreGraphState();
}