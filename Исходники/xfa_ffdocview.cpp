void CXFA_FFDocView::RunSubformIndexChange() {
  int32_t iSubforms = m_IndexChangedSubforms.GetSize();
  for (int32_t i = 0; i < iSubforms; i++) {
    CXFA_Node* pSubformNode = (CXFA_Node*)m_IndexChangedSubforms[i];
    CXFA_WidgetAcc* pWidgetAcc = (CXFA_WidgetAcc*)pSubformNode->GetWidgetData();
    if (!pWidgetAcc) {
      continue;
    }
    CXFA_EventParam eParam;
    eParam.m_eType = XFA_EVENT_IndexChange;
    eParam.m_pTarget = pWidgetAcc;
    pWidgetAcc->ProcessEvent(XFA_ATTRIBUTEENUM_IndexChange, &eParam);
  }
  m_IndexChangedSubforms.RemoveAll();
}