SystemTrayService::Handle SystemTrayServiceWindows::AddIcon(const RF_Draw::TrayIcon& Settings)
{
    // early exit if there are too many icons registered
    if(m_PImpl->m_IconData.Count() > MAX_WM_APP - WM_APP)
        return 0;

    RF_Mem::AutoPointer<NOTIFYICONDATA> notifyData(new NOTIFYICONDATA);

    RF_SysMem::Set(notifyData.Get(), 0, sizeof(NOTIFYICONDATA));
    notifyData->cbSize = sizeof(NOTIFYICONDATA);
    notifyData->hWnd = m_PImpl->m_HWND;
    notifyData->uVersion = NOTIFYICON_VERSION_4;
    notifyData->uFlags = NIF_GUID | NIF_MESSAGE;
    notifyData->uCallbackMessage = WM_APP + m_PImpl->m_IconData.Count();
    CoCreateGuid(&notifyData->guidItem);

    if(!Settings.Notification.IsEmpty())
    {
        notifyData->uFlags |= NIF_INFO | NIF_SHOWTIP;
        StringCchCopyA(notifyData->szInfo, ARRAYSIZE(notifyData->szInfo), Settings.Notification.c_str());
    }

    if(!Settings.Tooltip.IsEmpty())
    {
        notifyData->uFlags |= NIF_TIP;
        StringCchCopyA(notifyData->szTip, ARRAYSIZE(notifyData->szTip), Settings.Tooltip.c_str());
    }

    RF_IO::File icon;
    icon.SetLocation(Settings.Icon);
    if(icon.Exists())
    {
        RF_Type::String systemPath = Settings.Icon.GetComponents(RF_IO::UriComponents::Path);        
        int min = GetSystemMetrics(SM_CXSMICON);
        notifyData->hIcon = (HICON)LoadImage(NULL, systemPath.c_str(), IMAGE_ICON, 
                                             min, min, LR_LOADFROMFILE);
        if(notifyData->hIcon != 0)
        {
            notifyData->uFlags |= NIF_ICON;
        }
    }

    Handle handle = 0;
    SystemTrayService::Handle result = Shell_NotifyIcon(NIM_ADD, notifyData.Get());
    if(result)
    {
        handle = reinterpret_cast<Handle>(notifyData.Get());
        
        m_PImpl->m_IconData.Resize(m_PImpl->m_IconData.Count() + 1);
        auto& item = m_PImpl->m_IconData(m_PImpl->m_IconData.Count() - 1);
        m_PImpl->m_MessageLookup[notifyData->uCallbackMessage] = &item;
        m_PImpl->m_HandleLookup[handle] = &item;
        
        item.m_MenuHandle = m_PImpl->AddPopupMenu(Settings);
        item.m_NotificationData = notifyData;
    }

    return handle;
}