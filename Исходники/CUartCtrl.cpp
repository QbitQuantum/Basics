CUartCtrl::~CUartCtrl()
{
	CloseUart();
	DeleteCriticalSection(&m_csCom);
}