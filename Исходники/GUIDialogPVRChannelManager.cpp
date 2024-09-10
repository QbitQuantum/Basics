bool CGUIDialogPVRChannelManager::OnContextButton(int itemNumber, CONTEXT_BUTTON button)
{
  /* Check file item is in list range and get his pointer */
  if (itemNumber < 0 || itemNumber >= (int)m_channelItems->Size()) return false;

  CFileItemPtr pItem = m_channelItems->Get(itemNumber);
  if (!pItem)
    return false;

  if (button == CONTEXT_BUTTON_MOVE)
  {
    m_bMovingMode = true;
    pItem->Select(true);
  }
  else if (button == CONTEXT_BUTTON_EDIT_SOURCE)
  {
    CStdString strURL = pItem->GetProperty("StreamURL").asString();
    if (CGUIKeyboardFactory::ShowAndGetInput(strURL, g_localizeStrings.Get(19214), false))
      pItem->SetProperty("StreamURL", strURL);
  }
  return true;
}