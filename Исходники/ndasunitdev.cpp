HRESULT CNdasUnitImpl::ConnectUnitDevice(
	HNDAS *ndasHandle)
{
	//
	// Binding Address List
	//
	SOCKADDR_LPX localSockAddrLpx;
	SOCKET_ADDRESS localSocketAddress;
	localSocketAddress.iSockaddrLength = sizeof(SOCKADDR_LPX);
	localSocketAddress.lpSockaddr = reinterpret_cast<LPSOCKADDR>(&localSockAddrLpx);

	COMVERIFY(m_pParentNdasDevice->get_LocalAddress(&localSocketAddress));

	SOCKET_ADDRESS_LIST localAddressList;
	localAddressList.iAddressCount = 1;
	localAddressList.Address[0] = localSocketAddress;

	// Connection Information
	NDASCOMM_CONNECTION_INFO ci = {0};
	ci.Size = sizeof(NDASCOMM_CONNECTION_INFO);
	ci.AddressType = NDASCOMM_CIT_DEVICE_ID;
	COMVERIFY(m_pParentNdasDevice->get_NdasDeviceId(&ci.Address.DeviceId));
	ci.LoginType = NDASCOMM_LOGIN_TYPE_NORMAL;
	COMVERIFY(m_pParentNdasDevice->get_HardwarePassword(&ci.OEMCode.UI64Value));
	ci.Protocol = NDASCOMM_TRANSPORT_LPX;
	ci.UnitNo = m_unitDeviceId.UnitNo;
	ci.WriteAccess = FALSE;
	ci.BindingSocketAddressList = &localAddressList;

	*ndasHandle = ::NdasCommConnect(&ci);

	if (NULL == *ndasHandle)
	{
		HRESULT hr = AtlHresultFromLastError();
		XTLTRACE2(NDASSVC_NDASCOMM, TRACE_LEVEL_ERROR,
			"NdasCommConnect failed, hr=0x%X\n", hr);
		return hr;
	}

	return S_OK;
}