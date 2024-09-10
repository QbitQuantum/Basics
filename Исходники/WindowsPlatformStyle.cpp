void WindowsPlatformStyle::checkForModernStyle()
{
	if (QSysInfo::windowsVersion() >= QSysInfo::WV_10_0)
	{
		HIGHCONTRAST information = {0};
		information.cbSize = sizeof(HIGHCONTRAST);

		BOOL isSuccess(SystemParametersInfoW(SPI_GETHIGHCONTRAST, 0, &information, 0));

		m_isModernStyle = !(isSuccess && information.dwFlags & HCF_HIGHCONTRASTON);
	}
	else
	{
		m_isModernStyle = false;
	}
}