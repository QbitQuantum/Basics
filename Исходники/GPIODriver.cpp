CGPIODriver::CGPIODriver()
{
	// 打开驱动...	
	m_hGPIODriver = INVALID_HANDLE_VALUE;

	// 打开 GPIO 驱动
	OpenDriver();

}