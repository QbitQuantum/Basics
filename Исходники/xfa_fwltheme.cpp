void CXFA_FWLTheme::DrawText(CFWL_ThemeText* pParams) {
  if (pParams->m_wsText.IsEmpty())
    return;

  if (pParams->m_pWidget->GetClassID() == FWL_Type::MonthCalendar) {
    CXFA_FFWidget* pWidget = XFA_ThemeGetOuterWidget(pParams->m_pWidget);
    if (!pWidget)
      return;

    m_pTextOut->SetStyles(pParams->m_dwTTOStyles);
    m_pTextOut->SetAlignment(pParams->m_iTTOAlign);
    m_pTextOut->SetFont(m_pCalendarFont);
    m_pTextOut->SetFontSize(FWLTHEME_CAPACITY_FontSize);
    m_pTextOut->SetTextColor(FWLTHEME_CAPACITY_TextColor);
    if ((pParams->m_iPart == CFWL_Part::DatesIn) &&
        !(pParams->m_dwStates & FWL_ITEMSTATE_MCD_Flag) &&
        (pParams->m_dwStates &
         (CFWL_PartState_Hovered | CFWL_PartState_Selected))) {
      m_pTextOut->SetTextColor(0xFFFFFFFF);
    }
    if (pParams->m_iPart == CFWL_Part::Caption) {
      if (m_pMonthCalendarTP->GetThemeID(pParams->m_pWidget) == 0) {
        m_pTextOut->SetTextColor(ArgbEncode(0xff, 0, 153, 255));
      } else {
        m_pTextOut->SetTextColor(ArgbEncode(0xff, 128, 128, 0));
      }
    }
    CFX_Graphics* pGraphics = pParams->m_pGraphics;
    CFX_RenderDevice* pRenderDevice = pGraphics->GetRenderDevice();
    if (!pRenderDevice)
      return;

    m_pTextOut->SetRenderDevice(pRenderDevice);
    CFX_Matrix mtPart = pParams->m_matrix;
    CFX_Matrix* pMatrix = pGraphics->GetMatrix();
    if (pMatrix) {
      mtPart.Concat(*pMatrix);
    }
    m_pTextOut->SetMatrix(mtPart);
    m_pTextOut->DrawLogicText(pParams->m_wsText.c_str(),
                              pParams->m_wsText.GetLength(), pParams->m_rtPart);
    return;
  }
  CXFA_FFWidget* pWidget = XFA_ThemeGetOuterWidget(pParams->m_pWidget);
  if (!pWidget)
    return;

  CXFA_WidgetAcc* pAcc = pWidget->GetDataAcc();
  CFX_Graphics* pGraphics = pParams->m_pGraphics;
  CFX_RenderDevice* pRenderDevice = pGraphics->GetRenderDevice();
  if (!pRenderDevice)
    return;

  m_pTextOut->SetRenderDevice(pRenderDevice);
  m_pTextOut->SetStyles(pParams->m_dwTTOStyles);
  m_pTextOut->SetAlignment(pParams->m_iTTOAlign);
  m_pTextOut->SetFont(pAcc->GetFDEFont());
  m_pTextOut->SetFontSize(pAcc->GetFontSize());
  m_pTextOut->SetTextColor(pAcc->GetTextColor());
  CFX_Matrix mtPart = pParams->m_matrix;
  CFX_Matrix* pMatrix = pGraphics->GetMatrix();
  if (pMatrix)
    mtPart.Concat(*pMatrix);

  m_pTextOut->SetMatrix(mtPart);
  m_pTextOut->DrawLogicText(pParams->m_wsText.c_str(),
                            pParams->m_wsText.GetLength(), pParams->m_rtPart);
}