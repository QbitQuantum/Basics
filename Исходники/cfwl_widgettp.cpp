void CFWL_WidgetTP::DrawArrow(CFX_Graphics* pGraphics,
                              const CFX_RectF* pRect,
                              FWLTHEME_DIRECTION eDict,
                              FX_ARGB argSign,
                              CFX_Matrix* pMatrix) {
  bool bVert =
      (eDict == FWLTHEME_DIRECTION_Up || eDict == FWLTHEME_DIRECTION_Down);
  FX_FLOAT fLeft =
      (FX_FLOAT)(((pRect->width - (bVert ? 9 : 6)) / 2 + pRect->left) + 0.5);
  FX_FLOAT fTop =
      (FX_FLOAT)(((pRect->height - (bVert ? 6 : 9)) / 2 + pRect->top) + 0.5);
  CFX_Path path;
  switch (eDict) {
    case FWLTHEME_DIRECTION_Down: {
      path.MoveTo(CFX_PointF(fLeft, fTop + 1));
      path.LineTo(CFX_PointF(fLeft + 4, fTop + 5));
      path.LineTo(CFX_PointF(fLeft + 8, fTop + 1));
      path.LineTo(CFX_PointF(fLeft + 7, fTop));
      path.LineTo(CFX_PointF(fLeft + 4, fTop + 3));
      path.LineTo(CFX_PointF(fLeft + 1, fTop));
      break;
    }
    case FWLTHEME_DIRECTION_Up: {
      path.MoveTo(CFX_PointF(fLeft, fTop + 4));
      path.LineTo(CFX_PointF(fLeft + 4, fTop));
      path.LineTo(CFX_PointF(fLeft + 8, fTop + 4));
      path.LineTo(CFX_PointF(fLeft + 7, fTop + 5));
      path.LineTo(CFX_PointF(fLeft + 4, fTop + 2));
      path.LineTo(CFX_PointF(fLeft + 1, fTop + 5));
      break;
    }
    case FWLTHEME_DIRECTION_Right: {
      path.MoveTo(CFX_PointF(fLeft + 1, fTop));
      path.LineTo(CFX_PointF(fLeft + 5, fTop + 4));
      path.LineTo(CFX_PointF(fLeft + 1, fTop + 8));
      path.LineTo(CFX_PointF(fLeft, fTop + 7));
      path.LineTo(CFX_PointF(fLeft + 3, fTop + 4));
      path.LineTo(CFX_PointF(fLeft, fTop + 1));
      break;
    }
    case FWLTHEME_DIRECTION_Left: {
      path.MoveTo(CFX_PointF(fLeft, fTop + 4));
      path.LineTo(CFX_PointF(fLeft + 4, fTop));
      path.LineTo(CFX_PointF(fLeft + 5, fTop + 1));
      path.LineTo(CFX_PointF(fLeft + 2, fTop + 4));
      path.LineTo(CFX_PointF(fLeft + 5, fTop + 7));
      path.LineTo(CFX_PointF(fLeft + 4, fTop + 8));
      break;
    }
  }
  CFX_Color cr(argSign);
  pGraphics->SetFillColor(&cr);
  pGraphics->FillPath(&path, FXFILL_WINDING, pMatrix);
}