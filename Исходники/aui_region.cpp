void aui_Region::InitCommon(void)
{
#ifdef __AUI_USE_DIRECTX__
	m_doubleClickTimeOut    = GetDoubleClickTime();
#else
	m_doubleClickTimeOut    = 375;
#endif

	m_editGrabPoint.x       = -1;
	m_editGrabPoint.y       = -1;

    memset(&m_mouseState, 0, sizeof(m_mouseState));
}