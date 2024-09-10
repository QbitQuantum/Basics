CVkProto::~CVkProto()
{
	debugLogA("CVkProto::~CVkProto");
	Netlib_CloseHandle(m_hNetlibUser); 
	m_hNetlibUser = NULL;
	UninitQueue();
	UnInitMenus();
	if (m_hPopupClassError)
		Popup_UnregisterClass(m_hPopupClassError);
	if (m_hPopupClassNotification)
		Popup_UnregisterClass(m_hPopupClassNotification);
	{
		mir_cslock lck(csInstances);
		vk_Instances.remove(this);
	}
}