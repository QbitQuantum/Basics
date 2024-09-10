void CXFA_FFCheckButton::OnProcessEvent(CFWL_Event* pEvent) {
  CXFA_FFField::OnProcessEvent(pEvent);
  switch (pEvent->GetClassID()) {
    case CFWL_EventType::CheckStateChanged: {
      CXFA_EventParam eParam;
      eParam.m_eType = XFA_EVENT_Change;
      m_pDataAcc->GetValue(eParam.m_wsNewText, XFA_VALUEPICTURE_Raw);
      CXFA_WidgetAcc* pFFExclGroup = m_pDataAcc->GetExclGroup();
      if (ProcessCommittedData()) {
        eParam.m_pTarget = pFFExclGroup;
        if (pFFExclGroup) {
          m_pDocView->AddValidateWidget(pFFExclGroup);
          m_pDocView->AddCalculateWidgetAcc(pFFExclGroup);
          pFFExclGroup->ProcessEvent(XFA_ATTRIBUTEENUM_Change, &eParam);
        }
        eParam.m_pTarget = m_pDataAcc;
        m_pDataAcc->ProcessEvent(XFA_ATTRIBUTEENUM_Change, &eParam);
      } else {
        SetFWLCheckState(m_pDataAcc->GetCheckState());
      }
      if (pFFExclGroup) {
        eParam.m_pTarget = pFFExclGroup;
        pFFExclGroup->ProcessEvent(XFA_ATTRIBUTEENUM_Click, &eParam);
      }
      eParam.m_pTarget = m_pDataAcc;
      m_pDataAcc->ProcessEvent(XFA_ATTRIBUTEENUM_Click, &eParam);
      break;
    }
    default:
      break;
  }
  m_pOldDelegate->OnProcessEvent(pEvent);
}