HRESULT LoadVoices(void){
	HRESULT 					hr;
    ISpObjectToken 				*pToken;
	IEnumSpObjectTokens			*cpEnum;
	wchar_t						*pDescription, *p, *ptr, szBuffer[64];

	hr = _EnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);
	if(hr == S_OK){
		g_VoicesCount = 0;
		pDescription = (wchar_t *)CoTaskMemAlloc(128 * sizeof(wchar_t));
		while(IEnumSpObjectTokens_Next(cpEnum, 1, &pToken, NULL) == S_OK){
			hr = _GetDescription(pToken, &pDescription);
			if(SUCCEEDED(hr)){
				g_VoicesCount++;
				wcscpy(g_PVoices[g_VoicesCount - 1].name, pDescription);
				g_PVoices[g_VoicesCount - 1].token = pToken;
				GetPrivateProfileStringW(S_VOICES, pDescription, NULL, szBuffer, 64, g_NotePaths.INIFile);
				if(*szBuffer){
					p = wcstok(szBuffer, L"|", &ptr);
					g_PVoices[g_VoicesCount - 1].rate = _wtol(p);
					p = wcstok(NULL, L"|", &ptr);
					g_PVoices[g_VoicesCount - 1].volume = (unsigned short)_wtoi(p);
					g_PVoices[g_VoicesCount - 1].pitch = (short)_wtoi(ptr);
				}
				else{
					ISpVoice		*pVoice = CreateVoice();
					ISpVoice_SetVoice(pVoice, (ISpObjectToken *)g_PVoices[g_VoicesCount - 1].token);
					ISpVoice_GetVolume(pVoice, &g_PVoices[g_VoicesCount - 1].volume);
					ISpVoice_GetRate(pVoice, &g_PVoices[g_VoicesCount - 1].rate);
					g_PVoices[g_VoicesCount - 1].pitch = 0;
					ReleaseVoice(pVoice);
				}
				if(g_VoicesCount == NELEMS(g_PVoices))
					break;
			}
			if (FAILED(hr))
            {
                ISpObjectToken_Release(pToken);
				break;
            }
		}
		CoTaskMemFree(pDescription);
	}
	else
    {
        hr = SPERR_NO_MORE_ITEMS;
    }
    return hr;
}