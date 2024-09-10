bool CTrayIcon::CreateTrayBallon(SString strText, eTrayIconType trayIconType, bool useSound)
{
    if (!m_bTrayIconExists)
        if (!CreateTrayIcon())
            return false;

    auto currentTime = GetTickCount64_();

    if ((currentTime - m_llLastBalloonTime) < TRAY_BALLOON_INTERVAL)
        return false;
    else
        m_llLastBalloonTime = currentTime;

    m_pNID->dwInfoFlags = 0;
    m_pNID->uFlags = NIF_ICON | NIF_TIP | NIF_INFO;
    StringCchCopyW(m_pNID->szInfo, ARRAYSIZE(m_pNID->szInfo), SharedUtil::MbUTF8ToUTF16(strText).c_str());

    switch (trayIconType)
    {
        case ICON_TYPE_INFO:
            m_pNID->dwInfoFlags |= NIIF_INFO;
            break;
        case ICON_TYPE_WARNING:
            m_pNID->dwInfoFlags |= NIIF_WARNING;
            break;
        case ICON_TYPE_ERROR:
            m_pNID->dwInfoFlags |= NIIF_ERROR;
            break;
        case ICON_TYPE_DEFAULT:
        default:
            break;
    }

    if (!useSound)
        m_pNID->dwInfoFlags |= NIIF_NOSOUND;

    return Shell_NotifyIconW(NIM_MODIFY, m_pNID) == TRUE;
}