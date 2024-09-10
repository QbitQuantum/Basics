void sendKeyStrokes (std::wstring * s, bool noInternalActions = false)//Send Keys Strokes
{
	HWND hwnd = GetFocus();

	int cInputs = s->length() * 2;

	INPUT * ip = new INPUT[cInputs];

	for(int i=0, ii=0; i < s->length(); i++, ii++){
		ip[ii].type = INPUT_KEYBOARD;
		ip[ii].ki.dwExtraInfo = 0xDEADC0DE;
		ip[ii].ki.dwFlags = KEYEVENTF_UNICODE;
		ip[ii].ki.time = 0;
		ip[ii].ki.wScan = s->at(i);
		ip[ii].ki.wVk = 0;
		//SendInput(1, &ip, sizeof(INPUT));

		ii++;

		ip[ii].type = INPUT_KEYBOARD;
		ip[ii].ki.dwExtraInfo = 0;
		ip[ii].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
		ip[ii].ki.time = 0;
		ip[ii].ki.wScan = s->at(i);
		ip[ii].ki.wVk = 0;
		//SendInput(1, &ip, sizeof(INPUT));
	}

	int cSent = SendInput(cInputs, ip, sizeof(INPUT));
	Debug(L"cInputs=%d, cSent=%d\n",cInputs, cSent);

	if (noInternalActions == false) {
		InternalEditor.AppendText(s->c_str(), s->length());
	}
}