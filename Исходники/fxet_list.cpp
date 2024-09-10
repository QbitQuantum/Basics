int32_t CFX_ListCtrl::FindNext(int32_t nIndex, FX_WCHAR nChar) const {
  int32_t nCircleIndex = nIndex;

  for (int32_t i = 0, sz = m_aListItems.GetSize(); i < sz; i++) {
    nCircleIndex++;
    if (nCircleIndex >= sz)
      nCircleIndex = 0;

    if (CFX_ListItem* pListItem = m_aListItems.GetAt(nCircleIndex)) {
      if (Toupper(pListItem->GetFirstChar()) == Toupper(nChar))
        return nCircleIndex;
    }
  }

  return nCircleIndex;
}