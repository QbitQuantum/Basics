ScreenLockListenerWin::~ScreenLockListenerWin()
{
    HWND h = reinterpret_cast<HWND>(static_cast<QWidget*>(parent())->winId());
    WTSUnRegisterSessionNotification(h);

    if (m_powerNotificationHandle) {
        UnregisterPowerSettingNotification(reinterpret_cast<HPOWERNOTIFY>(m_powerNotificationHandle));
    }
}