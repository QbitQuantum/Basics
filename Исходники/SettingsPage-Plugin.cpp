void COptionPluginPage::HleAudioChanged(UINT /*Code*/, int id, HWND /*ctl*/)
{
    for (ButtonList::iterator iter = m_ButtonList.begin(); iter != m_ButtonList.end(); iter++)
    {
        CModifiedButton * Button = iter->second;
        if ((int)Button->GetMenu() != id)
        {
            continue;
        }
        if ((Button->GetCheck() & BST_CHECKED) != 0)
        {
            int res = MessageBoxW(m_hWnd, wGS(MSG_SET_HLE_AUD_MSG).c_str(), wGS(MSG_SET_HLE_AUD_TITLE).c_str(), MB_ICONWARNING | MB_YESNO);
            if (res != IDYES)
            {
                Button->SetCheck(BST_UNCHECKED);
                return;
            }
        }
        Button->SetChanged(true);
        SendMessage(GetParent(), PSM_CHANGED, (WPARAM)m_hWnd, 0);
        break;
    }
}