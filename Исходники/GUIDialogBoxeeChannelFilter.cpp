bool CGUIDialogBoxeeChannelFilter::OnClick(CGUIMessage& message)
{
  int controlId = message.GetSenderId();
  CGUIMessage msg(GUI_MSG_ITEM_SELECTED, GetID(), controlId);
  g_windowManager.SendMessage(msg);
  int itemIndex = msg.GetParam1();

  CGUIMessage msg1(GUI_MSG_GET_ITEM, GetID(), controlId, itemIndex);
  OnMessage(msg1);

  CFileItemPtr clickedLinkFileItem = boost::static_pointer_cast<CFileItem>(msg1.GetItem());
  clickedLinkFileItem->Select(!clickedLinkFileItem->IsSelected());

  CLog::Log(LOGDEBUG,"CGUIDialogBoxeeChannelFilter::OnClick - after update item [label=%s][IsSelected=%d]. [index=%d][controlId=%d] (cf)",clickedLinkFileItem->GetLabel().c_str(),clickedLinkFileItem->IsSelected(),itemIndex,controlId);

  CStdString sourceid = clickedLinkFileItem->GetProperty("sourceid");
  bool isChannelInExcluded = (m_excludedChannels.find(sourceid) != m_excludedChannels.end());

  if (isChannelInExcluded)
  {
    // channel WAS excluded
    if (clickedLinkFileItem->IsSelected())
    {
      // set to show -> remove from excluded set
      m_excludedChannels.erase(sourceid);
    }
  }
  else
  {
    // channel WASN'T excluded
    if (!clickedLinkFileItem->IsSelected())
    {
      // set to NOT show -> insert to excluded set
      m_excludedChannels.insert(sourceid);
    }
  }

  m_dirty = true;

  return true;
}