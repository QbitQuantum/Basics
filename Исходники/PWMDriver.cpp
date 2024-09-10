CPWMDriver::CPWMDriver()
{
	m_hPWMDriver = INVALID_HANDLE_VALUE;

	OpenDriver();
}