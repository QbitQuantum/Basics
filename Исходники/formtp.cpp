FX_BOOL CFWL_FormTP::DrawBackground(CFWL_ThemeBackground* pParams) {
  if (!pParams)
    return FALSE;
  int32_t iActive = 0;
  if (pParams->m_dwStates & FWL_PARTSTATE_FRM_Inactive) {
    iActive = 1;
  }
  FWLTHEME_STATE eState = FWLTHEME_STATE_Normal;
  switch (pParams->m_dwStates & 0x03) {
    case FWL_PARTSTATE_FRM_Hover: {
      eState = FWLTHEME_STATE_Hover;
      break;
    }
    case FWL_PARTSTATE_FRM_Pressed: {
      eState = FWLTHEME_STATE_Pressed;
      break;
    }
    case FWL_PARTSTATE_FRM_Disabled: {
      eState = FWLTHEME_STATE_Disabale;
      break;
    }
    default: {}
  }
  switch (pParams->m_iPart) {
    case FWL_PART_FRM_Border: {
      DrawFormBorder(pParams->m_pGraphics, &pParams->m_rtPart, eState,
                     &pParams->m_matrix, iActive);
      break;
    }
    case FWL_PART_FRM_Edge: {
      DrawEdge(pParams->m_pGraphics, pParams->m_pWidget->GetStyles(),
               &pParams->m_rtPart, &pParams->m_matrix);
      break;
    }
    case FWL_PART_FRM_Background: {
      FillBackground(pParams->m_pGraphics, &pParams->m_rtPart,
                     &pParams->m_matrix);
      break;
    }
    case FWL_PART_FRM_Caption: {
      DrawCaption(pParams->m_pGraphics, &pParams->m_rtPart, eState,
                  &pParams->m_matrix, iActive);
      break;
    }
    case FWL_PART_FRM_NarrowCaption: {
      DrawNarrowCaption(pParams->m_pGraphics, &pParams->m_rtPart, eState,
                        &pParams->m_matrix, iActive);
      break;
    }
    case FWL_PART_FRM_CloseBox: {
      DrawCloseBox(pParams->m_pGraphics, &pParams->m_rtPart, eState,
                   &pParams->m_matrix, iActive);
      break;
    }
    case FWL_PART_FRM_MinimizeBox: {
      DrawMinimizeBox(pParams->m_pGraphics, &pParams->m_rtPart, eState,
                      &pParams->m_matrix, iActive);
      break;
    }
    case FWL_PART_FRM_MaximizeBox: {
      DrawMaximizeBox(pParams->m_pGraphics, &pParams->m_rtPart, eState,
                      pParams->m_dwData, &pParams->m_matrix, iActive);
      break;
    }
    case FWL_PART_FRM_Icon: {
      DrawIconImage(pParams->m_pGraphics, pParams->m_pImage, &pParams->m_rtPart,
                    eState, &pParams->m_matrix, iActive);
      break;
    }
    default: {}
  }
  return TRUE;
}