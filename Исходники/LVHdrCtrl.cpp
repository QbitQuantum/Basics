BOOL CLVHdrCtrl::OnDrop(CWnd* /* pWnd */, COleDataObject* pDataObject,
                        DROPEFFECT /* dropEffect */, CPoint /* point */)
{
  // On Drop of column from Column Chooser Dialog onto Header
  if (!pDataObject->IsDataAvailable(m_ccddCPFID, NULL))
    return FALSE;

  HGLOBAL hGlobal;
  hGlobal = pDataObject->GetGlobalData(m_ccddCPFID);

  LPCWSTR pData = (LPCWSTR)GlobalLock(hGlobal);
  ASSERT(pData != NULL);

  DWORD procID;
  int iDDType, iType;

  swscanf_s(pData, L"%08x%02x%02x", &procID, &iDDType, &iType);

  // Check if it is ours?
  // - we don't accept drop from other instances of PWS
  // - we only accept drops from our ColumnChooser or our Header
  // - standard moving within the header only available if CC dialog not visible
  if ((procID != GetCurrentProcessId()) || (iDDType != FROMCC)) {
    GlobalUnlock(hGlobal);
    return FALSE;
  }

  int iAfterIndex;
  if (iType != CItemData::UUID) {
    // Get index of column we are on
    HDHITTESTINFO hdhti;
    hdhti.pt = CPoint(::GetMessagePos());
    hdhti.flags = 0;
    ScreenToClient(&hdhti.pt);
    ::SendMessage(this->GetSafeHwnd(), HDM_HITTEST, 0, (LPARAM) &hdhti);
    iAfterIndex = hdhti.iItem;
  } else
    iAfterIndex = 0;

  // Now add it but only if not trying to place to the left of the icon
  BOOL brc = TRUE;
  HDITEM hdi = {0};
  hdi.mask = HDI_LPARAM;
  GetItem(0, &hdi);
  if (hdi.lParam == CItemData::UUID && iAfterIndex == 0)
    brc = FALSE;
  else
    ::SendMessage(AfxGetApp()->m_pMainWnd->GetSafeHwnd(),
                  PWS_MSG_CCTOHDR_DD_COMPLETE, (WPARAM)iType, (LPARAM)iAfterIndex);

  GlobalUnlock(hGlobal);

  GetParent()->SetFocus();
  return brc;
}