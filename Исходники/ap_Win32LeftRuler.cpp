HWND AP_Win32LeftRuler::createWindow(HWND hwndContainer,
									UT_uint32 left, UT_uint32 top,
									UT_uint32 height)
{
		
	XAP_Win32App * app = static_cast<XAP_Win32App *>(XAP_App::getApp());
	m_hwndLeftRuler = UT_CreateWindowEx(0, s_LeftRulerWndClassName, NULL,
									 WS_CHILD | WS_VISIBLE,
									 left, top, s_iFixedWidth, height,
									 hwndContainer, NULL, app->getInstance(), NULL);
	UT_return_val_if_fail (m_hwndLeftRuler,0);
	SWL(m_hwndLeftRuler, this);
	
	
	DELETEP(m_pG);
	GR_Win32AllocInfo ai(GetDC(m_hwndLeftRuler), m_hwndLeftRuler);
	GR_Win32Graphics * pG = (GR_Win32Graphics *)XAP_App::getApp()->newGraphics(ai);

	m_pG = pG;
	UT_return_val_if_fail (pG, 0);
	pG->init3dColors();
	
	RECT rSize;
	GetClientRect(m_hwndLeftRuler,&rSize);
	setHeight(rSize.bottom);
	setWidth(rSize.right);

	return m_hwndLeftRuler;
}