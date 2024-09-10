bool NavigatorPanelUI::SelectItem(int idx)
{
    if (idx == m_curSel)  return true;
    if (m_curSel >= 0)  {
        ControlUI* ctrl = GetItem(m_curSel);
        IListItemUI* listItem = static_cast<IListItemUI*>(ctrl->GetInterface("ListItem"));
        if (listItem != NULL)  listItem->Select(false);
    }
    m_curSel = idx;
    if (m_curSel >= 0)  {
        ControlUI* ctrl = GetItem(m_curSel);
        IListItemUI* listItem = static_cast<IListItemUI*>(ctrl->GetInterface("ListItem"));
        if (listItem == NULL)  return false;
        listItem->Select(true);
        if (m_mgr != NULL)  m_mgr->SendNotify(ctrl, "itemclick");
    }
    if (m_mgr != NULL)  m_mgr->SendNotify(this, "itemselect");
    Invalidate();
    return true;
}