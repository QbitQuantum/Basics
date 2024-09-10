//////////////////////////////////////////////////////////////////////////////
// CElcAudioDeviceEnumerator
int CElcAudioDeviceEnumerator::Enumerate(BOOL bCapture, BOOL bFilterPrivateDevice)
{
	Release();

	m_bCapture = bCapture;

	BOOL bSuccessful = FALSE;
	if (bCapture) {
		IDSoundCaptureEnumModule* pCaptureEnum = NULL;
		if (VOIP_FAILED(IDSoundCaptureEnumModule::Create(pCaptureEnum)))
			return FALSE;

		do {
			int nCount = pCaptureEnum->GetCount();

			GUID guidNull = GUID_NULL;
			for (int i=1; i < nCount; i++) {

				// filter private devices
				if (bFilterPrivateDevice) {
					LPCTSTR lpszDevicePnpId = pCaptureEnum->GetDevicePnpID(i);
					if (IsXVALoopback(lpszDevicePnpId)
						|| IsXA001AURecord(lpszDevicePnpId)
						|| IsXA001AULoopback(lpszDevicePnpId))
					{
						continue;
					}
				}

				IAudioMixerModule* pInputMixer = NULL;
				if (VOIP_FAILED(IAudioMixerModule::Create(*pCaptureEnum->GetDeviceID(i), TRUE, pInputMixer))) {
					//ASSERT(0);
					continue;
				}

				CElcAudioCaptureItem * pItem = new CElcAudioCaptureItem;

				pItem->m_nType = ELCDT_AUDIO_CAPTURE;
				ElcGuid2String(pCaptureEnum->GetDeviceID(i), pItem->m_strDeviceId);
				pItem->m_strDevicePnpId = pCaptureEnum->GetDevicePnpID(i);
				pItem->m_strDeviceName = pCaptureEnum->GetDeviceName(i);

				int nLineCount = pInputMixer->GetLineCount();
				for (int i=0; i < nLineCount; i++)
					pItem->m_arrInput.push_back(pInputMixer->GetLineName(i));

				VOIP_DESTROY_MODULE(pInputMixer);

				m_arrItem.push_back(pItem);
			}

			bSuccessful = TRUE;
		} while(0);

		VOIP_DESTROY_MODULE(pCaptureEnum);
	}
	else {
		IDSoundRendererEnumModule* pRendererEnum = NULL;
		if (VOIP_FAILED(IDSoundRendererEnumModule::Create(pRendererEnum)))
			return FALSE;

		do {
			int nCount = pRendererEnum->GetCount();
			if (nCount <= 1)
				break;

			GUID guidNull = GUID_NULL;
			for (int i=1; i < nCount; i++) {

				// filter private devices
				if (bFilterPrivateDevice) {
					LPCTSTR lpszDevicePnpId = pRendererEnum->GetDevicePnpID(i);
					if (IsXVAPlayback(lpszDevicePnpId)
						|| IsXA001AUPlayback(lpszDevicePnpId)
						|| IsXA001AUVoice(lpszDevicePnpId))
					{
						continue;
					}
				}

				CElcAudioRendererItem * pItem = new CElcAudioRendererItem;
				pItem->m_nType = ELCDT_AUDIO_RENDERER;
				ElcGuid2String(pRendererEnum->GetDeviceID(i), pItem->m_strDeviceId);
				pItem->m_strDevicePnpId = pRendererEnum->GetDevicePnpID(i);
				pItem->m_strDeviceName = pRendererEnum->GetDeviceName(i);
				m_arrItem.push_back(pItem);
			}
			bSuccessful = TRUE;
		} while(0);

		VOIP_DESTROY_MODULE(pRendererEnum);
	}

	return (int)m_arrItem.size();
}