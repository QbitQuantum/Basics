int	InputInterface::HandleRawInput(HRAWINPUT* pRawData){
	if (pRawData == NULL){
		return false;
	}
	
	UINT dwSize;
	GetRawInputData(*pRawData, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));


	BYTE lpb[4096] = { 0 };// = new BYTE[dwSize];
	//if (lpb == NULL)
	//{
		//return 0;
	//}
	int readSize = GetRawInputData((HRAWINPUT)*pRawData, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
	if (readSize != dwSize){
		OutputDebugString(L"ERROR:  GetRawInputData didn't return correct size!\n" ) ; 
		return 0;
	}
	
	RAWINPUT* pRaw = (RAWINPUT*)lpb;
	if (pRaw->header.dwType == RIM_TYPEHID){
		RID_DEVICE_INFO device_info = { 0 };
		unsigned int SizeInBytes = sizeof(RID_DEVICE_INFO);
		m_DualShockMutex.Open();
		for (unsigned int i = 0; i < 4; i++){
			if (m_DualShock4Info[i].hDevice == pRaw->header.hDevice && m_DualShock4Info[i].Connected){
				const int index = i;
				DualShock4State state = { 0 };
				ProcessDS4(state, &pRaw->data.hid);
				

				break;
			}
		}
		m_DualShockMutex.Close();
		
	}
	return true;
}