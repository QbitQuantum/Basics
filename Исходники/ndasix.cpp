VOID
CNdasIXServer::OnIXPrimaryUpdate(
	CLpxDatagramSocket& sock,
	CONST SOCKADDR_LPX* pRemoteAddr,
	CONST LSINFOX_PRIMARY_UPDATE* pData)
{
	NDAS_UNITDEVICE_ID unitDeviceId = { 
		{ 
			pData->NetDiskNode[0], pData->NetDiskNode[1],
			pData->NetDiskNode[2], pData->NetDiskNode[3],
			pData->NetDiskNode[4], pData->NetDiskNode[5]
		}, 
		pData->UnitDiskNo
	};

	CNdasUnitDevicePtr pUnitDevice = pGetNdasUnitDevice(unitDeviceId);
	if (0 == pUnitDevice.get()) {
		//
		// Discard non-discovered unit device
		//
		return;
	}

	NDAS_UNITDEVICE_PRIMARY_HOST_INFO hostinfo;

	::CopyMemory(
		hostinfo.Host.Node, 
		pData->PrimaryNode,
		sizeof(hostinfo.Host.Node));

	hostinfo.Host.Port = NTOHS(pData->PrimaryPort);
	hostinfo.SWMajorVersion = pData->SWMajorVersion;
	hostinfo.SWMinorVersion = pData->SWMinorVersion;
	hostinfo.SWBuildNumber = pData->SWBuildNumber;
	hostinfo.NDFSCompatVersion = pData->NDFSCompatVersion;
	hostinfo.NDFSVersion = pData->NDFSVersion;

	XTLTRACE2(NDASSVC_IX, TRACE_LEVEL_RESERVED6,
		"LSINFOX_PRIMATE_UPDATE_MESSAGE: %02X:%02X:%02X:%02X:%02X:%02X@%d\n",
		pData->NetDiskNode[0],
		pData->NetDiskNode[1],
		pData->NetDiskNode[2],
		pData->NetDiskNode[3],
		pData->NetDiskNode[4],
		pData->NetDiskNode[5],
		pData->UnitDiskNo);

	pUnitDevice->UpdatePrimaryHostInfo(hostinfo);

	return;
}