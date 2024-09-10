BOOL
CNdasDeviceRegistrar::Unregister(DWORD dwSlotNo)
{
	ximeta::CAutoLock autolock(this);

	DeviceSlotMap::iterator itrSlot = 
		m_deviceSlotMap.find(dwSlotNo);

	if (m_deviceSlotMap.end() == itrSlot) {
		// TODO: Make more specific error code
		::SetLastError(NDASHLPSVC_ERROR_DEVICE_ENTRY_NOT_FOUND);
		return FALSE;
	}

	PCNdasDevice pDevice = itrSlot->second;

	if (pDevice->GetStatus() != NDAS_DEVICE_STATUS_DISABLED) {
		// TODO: ::SetLastError(NDAS_ERROR_CANNOT_UNREGISTER_ENABLED_DEVICE);
		// TODO: Make more specific error code
		::SetLastError(NDASHLPSVC_ERROR_CANNOT_UNREGISTER_ENABLED_DEVICE);
		return FALSE;
	}

	DeviceIdMap::iterator itrId = 
		m_deviceIdMap.find(pDevice->GetDeviceId());

	_ASSERTE(m_deviceIdMap.end() != itrId);

	m_deviceIdMap.erase(itrId);
	m_deviceSlotMap.erase(itrSlot);
	m_pbSlotOccupied[dwSlotNo] = FALSE;

	pDevice->Release();

	TCHAR szContainer[30];
	HRESULT hr = ::StringCchPrintf(szContainer, 30, TEXT("Devices\\%04d"), dwSlotNo);
	_ASSERT(SUCCEEDED(hr));

	BOOL fSuccess = _NdasSystemCfg.DeleteContainer(szContainer, FALSE);
	
	if (!fSuccess) {
		DPWarningEx(
			_FT("Deleting registration entry from the registry failed at %s.\n"), 
			szContainer);
	}

	CNdasInstanceManager* pInstMan = CNdasInstanceManager::Instance();
	_ASSERTE(NULL != pInstMan);

	CNdasEventPublisher* pEventPublisher = pInstMan->GetEventPublisher();
	_ASSERTE(NULL != pEventPublisher);

	(void) pEventPublisher->DeviceEntryChanged();

	return TRUE;

}