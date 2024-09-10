CCherryNotificationDialog::CCherryNotificationDialog()
:
m_bWinXPOrLater(IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0))
{
	Initialize();
}