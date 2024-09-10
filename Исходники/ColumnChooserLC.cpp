BOOL CColumnChooserLC::OnDrop(CWnd* /* pWnd */, COleDataObject* pDataObject,
                              DROPEFFECT /* dropEffect */, CPoint /* point */)
{
  // On Drop of column from Header onto Column Chooser Dialog
  if (!pDataObject->IsDataAvailable(m_ccddCPFID, NULL))
    return FALSE;

  HGLOBAL hGlobal;
  hGlobal = pDataObject->GetGlobalData(m_ccddCPFID);

  LPCWSTR pData = (LPCWSTR)GlobalLock(hGlobal);
  ASSERT(pData != NULL);

  DWORD procID;
  int iDDType, dw_type, iLen;

#if (_MSC_VER >= 1400)
  swscanf_s(pData, L"%08x%02x%02x%04x", &procID, &iDDType, &dw_type, &iLen);
#else
  swscanf(pData, L"08x%02x%02x%04x", &procID, &iDDType, &dw_type, &iLen);
#endif

  // Check if it is ours?
  // - we don't accept drop from other instances of PWS
  // Check if it is from List View HeaderCtrl?
  // - we don't accept drop from anything else
  if ((procID != GetCurrentProcessId()) || (iDDType != FROMHDR)) {
    GlobalUnlock(hGlobal);
    return FALSE;
  }

  // Now add it
  const CString cs_header(pData + 16, iLen);
  int iItem = InsertItem(0, cs_header);
  SetItemData(iItem, dw_type);
  SortItems(CCLCCompareProc, (LPARAM)this);

  GlobalUnlock(hGlobal);

  GetParent()->SetFocus();
  return TRUE;
}