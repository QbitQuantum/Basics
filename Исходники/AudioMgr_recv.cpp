DWORD CAudioMgr_recv::AudioOutThreadProc(LPVOID lpParameter)
{
	CAudioMgr_recv* pMgr = (CAudioMgr_recv*)lpParameter;
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		switch(msg.message)
		{
		case IOM_AUDIO:
			pMgr->m_audioplay.Play((char*)msg.lParam,(int)msg.wParam);
			break;
		case WOM_DONE:
			{
				WAVEHDR* pwh=(WAVEHDR*)msg.lParam;
				waveOutUnprepareHeader((HWAVEOUT)msg.wParam,pwh,sizeof(WAVEHDR));
				delete []pwh->lpData;
				delete pwh;
			}
			break;
		}
	}
	return msg.wParam;
}