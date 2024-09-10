FX_BOOL _SendPreSaveToXFADoc(CPDFXFA_Document* pDocument,
                             CFX_PtrArray& fileList) {
  if (pDocument->GetDocType() != DOCTYPE_DYNAMIC_XFA &&
      pDocument->GetDocType() != DOCTYPE_STATIC_XFA)
    return TRUE;
  IXFA_DocView* pXFADocView = pDocument->GetXFADocView();
  if (NULL == pXFADocView)
    return TRUE;
  IXFA_WidgetHandler* pWidgetHander = pXFADocView->GetWidgetHandler();
  CXFA_WidgetAcc* pWidgetAcc = NULL;
  IXFA_WidgetAccIterator* pWidgetAccIterator =
      pXFADocView->CreateWidgetAccIterator();
  pWidgetAcc = pWidgetAccIterator->MoveToNext();
  while (pWidgetAcc) {
    CXFA_EventParam preParam;
    preParam.m_eType = XFA_EVENT_PreSave;
    pWidgetHander->ProcessEvent(pWidgetAcc, &preParam);
    pWidgetAcc = pWidgetAccIterator->MoveToNext();
  }
  pWidgetAccIterator->Release();
  pXFADocView->UpdateDocView();
  return _SaveXFADocumentData(pDocument, fileList);
}