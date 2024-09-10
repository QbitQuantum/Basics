bool CPDFXFA_DocEnvironment::OnBeforeNotifySubmit() {
  if (m_pContext->GetDocType() != DOCTYPE_DYNAMIC_XFA &&
      m_pContext->GetDocType() != DOCTYPE_STATIC_XFA) {
    return true;
  }

  if (!m_pContext->GetXFADocView())
    return true;

  CXFA_FFWidgetHandler* pWidgetHandler =
      m_pContext->GetXFADocView()->GetWidgetHandler();
  if (!pWidgetHandler)
    return true;

  std::unique_ptr<CXFA_WidgetAccIterator> pWidgetAccIterator(
      m_pContext->GetXFADocView()->CreateWidgetAccIterator());
  if (pWidgetAccIterator) {
    CXFA_EventParam Param;
    Param.m_eType = XFA_EVENT_PreSubmit;
    while (CXFA_WidgetAcc* pWidgetAcc = pWidgetAccIterator->MoveToNext())
      pWidgetHandler->ProcessEvent(pWidgetAcc, &Param);
  }

  pWidgetAccIterator.reset(
      m_pContext->GetXFADocView()->CreateWidgetAccIterator());
  if (!pWidgetAccIterator)
    return true;

  CXFA_WidgetAcc* pWidgetAcc = pWidgetAccIterator->MoveToNext();
  pWidgetAcc = pWidgetAccIterator->MoveToNext();
  while (pWidgetAcc) {
    int fRet = pWidgetAcc->ProcessValidate(-1);
    if (fRet == XFA_EVENTERROR_Error) {
      CPDFSDK_FormFillEnvironment* pFormFillEnv = m_pContext->GetFormFillEnv();
      if (!pFormFillEnv)
        return false;

      CFX_WideString ws;
      ws.FromLocal(IDS_XFA_Validate_Input);
      CFX_ByteString bs = ws.UTF16LE_Encode();
      int len = bs.GetLength();
      pFormFillEnv->Alert((FPDF_WIDESTRING)bs.GetBuffer(len),
                          (FPDF_WIDESTRING)L"", 0, 1);
      bs.ReleaseBuffer(len);
      return false;
    }
    pWidgetAcc = pWidgetAccIterator->MoveToNext();
  }
  m_pContext->GetXFADocView()->UpdateDocView();

  return true;
}