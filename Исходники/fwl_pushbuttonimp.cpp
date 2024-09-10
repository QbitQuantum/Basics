FWL_ERR CFWL_PushButtonImp::DrawWidget(CFX_Graphics* pGraphics,
                                       const CFX_Matrix* pMatrix) {
  if (!pGraphics)
    return FWL_ERR_Indefinite;
  if (!m_pProperties->m_pThemeProvider)
    return FWL_ERR_Indefinite;
  IFWL_PushButtonDP* pData =
      static_cast<IFWL_PushButtonDP*>(m_pProperties->m_pDataProvider);
  CFX_DIBitmap* pPicture = NULL;
  IFWL_ThemeProvider* pTheme = m_pProperties->m_pThemeProvider;
  if (HasBorder()) {
    DrawBorder(pGraphics, FWL_PART_PSB_Border, m_pProperties->m_pThemeProvider,
               pMatrix);
  }
  if (HasEdge()) {
    DrawEdge(pGraphics, FWL_PART_PSB_Edge, m_pProperties->m_pThemeProvider,
             pMatrix);
  }
  DrawBkground(pGraphics, m_pProperties->m_pThemeProvider, pMatrix);
  CFX_Matrix matrix;
  matrix.Concat(*pMatrix);
  FX_FLOAT iPicwidth = 0;
  FX_FLOAT ipicheight = 0;
  CFX_WideString wsCaption;
  if (pData) {
    pData->GetCaption(m_pInterface, wsCaption);
  }
  CFX_RectF rtText;
  rtText.Set(0, 0, 0, 0);
  if (!wsCaption.IsEmpty()) {
    CalcTextRect(wsCaption, pTheme, 0, m_iTTOAlign, rtText);
  }
  switch (m_pProperties->m_dwStyleExes & FWL_STYLEEXT_PSB_ModeMask) {
    case FWL_STYLEEXT_PSB_TextOnly:
      DrawText(pGraphics, m_pProperties->m_pThemeProvider, &matrix);
      break;
    case FWL_STYLEEXT_PSB_IconOnly:
      if (pData) {
        pPicture = pData->GetPicture(m_pInterface);
      }
      if (pPicture) {
        CFX_PointF point;
        switch (m_iTTOAlign) {
          case 0: {
            point.x = m_rtClient.left;
            point.y = m_rtClient.top;
            break;
          }
          case 1: {
            point.x = m_rtClient.left +
                      (m_rtClient.width / 2 - pPicture->GetWidth() / 2);
            point.y = m_rtClient.top;
            break;
          }
          case 2:
            point.x = m_rtClient.left + m_rtClient.width - pPicture->GetWidth();
            point.y = m_rtClient.top;
            break;
          case 4:
            point.x = m_rtClient.left;
            point.y = m_rtClient.top + m_rtClient.height / 2 -
                      pPicture->GetHeight() / 2;
            break;
          case 5:
            point.x = m_rtClient.left +
                      (m_rtClient.width / 2 - pPicture->GetWidth() / 2);
            point.y = m_rtClient.top + m_rtClient.height / 2 -
                      pPicture->GetHeight() / 2;
            break;
          case 6:
            point.x = m_rtClient.left + m_rtClient.width - pPicture->GetWidth();
            point.y = m_rtClient.top + m_rtClient.height / 2 -
                      pPicture->GetHeight() / 2;
            break;
          case 8:
            point.x = m_rtClient.left;
            point.y =
                m_rtClient.top + m_rtClient.height - pPicture->GetHeight();
            break;
          case 9:
            point.x = m_rtClient.left +
                      (m_rtClient.width / 2 - pPicture->GetWidth() / 2);
            point.y =
                m_rtClient.top + m_rtClient.height - pPicture->GetHeight();
            break;
          case 10:
            point.x = m_rtClient.left + m_rtClient.width - pPicture->GetWidth();
            point.y =
                m_rtClient.top + m_rtClient.height - pPicture->GetHeight();
            break;
        }
        pGraphics->DrawImage(pPicture, point, &matrix);
      }
      break;
    case FWL_STYLEEXT_PSB_TextIcon:
      if (pPicture) {
        CFX_PointF point;
        switch (m_iTTOAlign) {
          case 0: {
            point.x = m_rtClient.left;
            point.y = m_rtClient.top;
            iPicwidth = (FX_FLOAT)(pPicture->GetWidth() - 7);
            ipicheight =
                pPicture->GetHeight() / 2 - m_rtCaption.top - rtText.height / 2;
            break;
          }
          case 1: {
            point.x =
                m_rtClient.left + (m_rtClient.width / 2 -
                                   (pPicture->GetWidth() + rtText.width) / 2);
            point.y = m_rtClient.top;
            iPicwidth = pPicture->GetWidth() -
                        ((m_rtClient.width) / 2 - rtText.width / 2 - point.x) +
                        rtText.width / 2 - 7;
            ipicheight =
                pPicture->GetHeight() / 2 - m_rtCaption.top - rtText.height / 2;
            break;
          }
          case 2:
            point.x = m_rtClient.left + m_rtClient.width -
                      pPicture->GetWidth() - rtText.width;
            point.y = m_rtClient.top;
            iPicwidth = m_rtClient.left + m_rtClient.width - point.x -
                        pPicture->GetWidth() - rtText.width + 7;
            ipicheight =
                pPicture->GetHeight() / 2 - m_rtCaption.top - rtText.height / 2;
            break;
          case 4:
            point.x = m_rtClient.left;
            point.y = m_rtClient.top + m_rtClient.height / 2 -
                      pPicture->GetHeight() / 2;
            iPicwidth = m_rtClient.left + pPicture->GetWidth() - 7;
            break;
          case 5:
            point.x =
                m_rtClient.left + (m_rtClient.width / 2 -
                                   (pPicture->GetWidth() + rtText.width) / 2);
            point.y = m_rtClient.top + m_rtClient.height / 2 -
                      pPicture->GetHeight() / 2;
            iPicwidth = pPicture->GetWidth() -
                        ((m_rtClient.width) / 2 - rtText.width / 2 - point.x) +
                        rtText.width / 2 - 7;
            break;
          case 6:
            point.x = m_rtClient.left + m_rtClient.width -
                      pPicture->GetWidth() - rtText.width;
            point.y = m_rtClient.top + m_rtClient.height / 2 -
                      pPicture->GetHeight() / 2;
            iPicwidth = m_rtClient.left + m_rtClient.width - point.x -
                        pPicture->GetWidth() - rtText.width + 7;
            break;
          case 8:
            point.x = m_rtClient.left;
            point.y =
                m_rtClient.top + m_rtClient.height - pPicture->GetHeight();
            iPicwidth = (FX_FLOAT)(pPicture->GetWidth() - 7);
            ipicheight -= rtText.height / 2;
            break;
          case 9:
            point.x =
                m_rtClient.left + (m_rtClient.width / 2 -
                                   (pPicture->GetWidth() + rtText.width) / 2);
            point.y =
                m_rtClient.top + m_rtClient.height - pPicture->GetHeight();
            iPicwidth = pPicture->GetWidth() -
                        ((m_rtClient.width) / 2 - rtText.width / 2 - point.x) +
                        rtText.width / 2 - 7;
            ipicheight -= rtText.height / 2;
            break;
          case 10:
            point.x = m_rtClient.left + m_rtClient.width -
                      pPicture->GetWidth() - rtText.width;
            point.y =
                m_rtClient.top + m_rtClient.height - pPicture->GetHeight();
            iPicwidth = m_rtClient.left + m_rtClient.width - point.x -
                        pPicture->GetWidth() - rtText.width + 7;
            ipicheight -= rtText.height / 2;
            break;
        }
        pGraphics->DrawImage(pPicture, point, &matrix);
      }
      matrix.e += m_rtClient.left + iPicwidth;
      matrix.f += m_rtClient.top + ipicheight;
      DrawText(pGraphics, m_pProperties->m_pThemeProvider, &matrix);
      break;
  }
  return FWL_ERR_Succeeded;
}