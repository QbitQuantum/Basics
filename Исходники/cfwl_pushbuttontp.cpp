FX_BOOL CFWL_PushButtonTP::DrawBackground(CFWL_ThemeBackground* pParams) {
  switch (pParams->m_iPart) {
    case CFWL_Part::Border: {
      DrawBorder(pParams->m_pGraphics, &pParams->m_rtPart, &pParams->m_matrix);
      break;
    }
    case CFWL_Part::Edge: {
      DrawEdge(pParams->m_pGraphics, pParams->m_pWidget->GetStyles(),
               &pParams->m_rtPart, &pParams->m_matrix);
      break;
    }
    case CFWL_Part::Background: {
      CFX_RectF& rect = pParams->m_rtPart;
      FX_FLOAT fRight = rect.right();
      FX_FLOAT fBottom = rect.bottom();
      CFX_Path strokePath;
      strokePath.Create();
      strokePath.MoveTo(rect.left + PUSHBUTTON_SIZE_Corner, rect.top);
      strokePath.LineTo(fRight - PUSHBUTTON_SIZE_Corner, rect.top);
      strokePath.LineTo(fRight, rect.top + PUSHBUTTON_SIZE_Corner);
      strokePath.LineTo(fRight, fBottom - PUSHBUTTON_SIZE_Corner);
      strokePath.LineTo(fRight - PUSHBUTTON_SIZE_Corner, fBottom);
      strokePath.LineTo(rect.left + PUSHBUTTON_SIZE_Corner, fBottom);
      strokePath.LineTo(rect.left, fBottom - PUSHBUTTON_SIZE_Corner);
      strokePath.LineTo(rect.left, rect.top + PUSHBUTTON_SIZE_Corner);
      strokePath.LineTo(rect.left + PUSHBUTTON_SIZE_Corner, rect.top);
      CFX_Path fillPath;
      fillPath.Create();
      fillPath.AddSubpath(&strokePath);
      CFX_Graphics* pGraphics = pParams->m_pGraphics;
      pGraphics->SaveGraphState();
      CFX_RectF rtInner(rect);
      rtInner.Deflate(PUSHBUTTON_SIZE_Corner + 1, PUSHBUTTON_SIZE_Corner + 1,
                      PUSHBUTTON_SIZE_Corner, PUSHBUTTON_SIZE_Corner);
      fillPath.AddRectangle(rtInner.left, rtInner.top, rtInner.width,
                            rtInner.height);
      int32_t iColor = GetColorID(pParams->m_dwStates);
      DrawAxialShading(pGraphics, rect.left + PUSHBUTTON_SIZE_Corner, rect.top,
                       rect.left + PUSHBUTTON_SIZE_Corner, rect.bottom(),
                       m_pThemeData->clrStart[iColor],
                       m_pThemeData->clrEnd[iColor], &fillPath,
                       FXFILL_ALTERNATE, &pParams->m_matrix);
      CFX_Color crStroke(m_pThemeData->clrBorder[iColor]);
      pGraphics->SetStrokeColor(&crStroke);
      pGraphics->StrokePath(&strokePath, &pParams->m_matrix);
      fillPath.Clear();
      fillPath.AddRectangle(rtInner.left, rtInner.top, rtInner.width,
                            rtInner.height);
      CFX_Color crFill(m_pThemeData->clrFill[iColor]);
      pGraphics->SetFillColor(&crFill);
      pGraphics->FillPath(&fillPath, FXFILL_WINDING, &pParams->m_matrix);
      if (pParams->m_dwStates & CFWL_PartState_Focused) {
        rtInner.Inflate(1, 1, 0, 0);
        DrawFocus(pGraphics, &rtInner, &pParams->m_matrix);
      }
      pGraphics->RestoreGraphState();
      break;
    }
    default: {}
  }
  return TRUE;
}