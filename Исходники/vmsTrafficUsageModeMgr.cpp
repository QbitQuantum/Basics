void vmsTrafficUsageModeMgr::CheckIfBestInterfaceChanged ()
{
	vmsIpHelper iph;
	if (!iph.GetAdaptersInfo ())
		return;

	DWORD dwIfIndex;
	if (NO_ERROR != GetBestInterface (inet_addr ("8.8.8.8"), &dwIfIndex))
		return;

	PIP_ADAPTER_INFO pAdapter = iph.FindAdapterByIfIndex (dwIfIndex);
	if (!pAdapter)
		return;

	if (pAdapter->IpAddressList.IpAddress.String == m_strCurrentIP)
		return;

	if (!(m_dwState & TUMM_SPEEDS_INFO_CAN_BE_INCORRECT))
		SaveCurrentAdapterInfo ();

	std::string strAdapterAddress;
	for (UINT i = 0; i < pAdapter->AddressLength; i++)
	{
		char sz [10];
		itoa (pAdapter->Address [i], sz, 16);
		if (sz [1] == 0)
			strAdapterAddress += '0';
		strAdapterAddress += sz;
	}

	m_strCurrentAdapterAddress = strAdapterAddress;
	m_strCurrentIP = pAdapter->IpAddressList.IpAddress.String;

	vmsAUTOLOCKSECTION (m_csMisc);
	m_dwState |= TUMM_SPEEDS_INFO_CAN_BE_INCORRECT;
	vmsAUTOLOCKSECTION_UNLOCK (m_csMisc);

	vmsAUTOLOCKSECTION (m_csManageForSpeed);
	
	for (size_t i = 0; i < m_vpManageForSpeed.size (); i++)
	{
		ManageForSpeedItemsList *pList = m_vpManageForSpeed [i];

		for (size_t j = 0; j < pList->vItems.size (); j++)
			pList->vItems [j].state |= ManageForSpeedItem::MSIS_MAY_USE_NOT_CURRENT_ADAPTER;
	}
	vmsAUTOLOCKSECTION_UNLOCK (m_csManageForSpeed);

	ResetAllSpeedsInfo ();
}