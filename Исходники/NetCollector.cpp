long NetCollector::CollectFallback(NVDataItem *DataItems) 
{
	USES_CONVERSION;

	DWORD Status;

	DWORD NumIfEntries;

	Status = GetNumberOfInterfaces( &NumIfEntries);
	if (Status != NO_ERROR)
		return ERROR_SUCCESS;

	PMIB_IFTABLE IfTable = NULL;
	PMIB_IPADDRTABLE IPAddrTable = NULL;

	unsigned long IfLen = 0;
	unsigned long IpLen = 0;

	Status = GetIfTable(IfTable, &IfLen, TRUE);
	if (Status != ERROR_INSUFFICIENT_BUFFER)
		return ERROR_SUCCESS;

	Status = GetIpAddrTable(IPAddrTable, &IpLen, FALSE);
	if (Status != ERROR_INSUFFICIENT_BUFFER)
		return ERROR_SUCCESS;
	
	IfTable = (PMIB_IFTABLE) new char[IfLen];
	memset(IfTable, 0 , IfLen);

	IPAddrTable = (PMIB_IPADDRTABLE) new char[IpLen];
	memset(IPAddrTable, 0 , IpLen);

	Status = GetIfTable(IfTable, &IfLen, TRUE);
	if (Status != NO_ERROR) {
		delete IfTable;
		delete IPAddrTable;
		return ERROR_SUCCESS;
	}

	Status = GetIpAddrTable(IPAddrTable, &IpLen, FALSE);
	if (Status != NO_ERROR) {
		delete IfTable;
		delete IPAddrTable;
		return ERROR_SUCCESS;
	}

	DWORD CurrIf;

	char TransString[64];
	char IPString[64];

	PMIB_IFROW CurrEntry = NULL;

	for (CurrIf = 0, CurrEntry = IfTable->table;
		 CurrIf < IfTable->dwNumEntries; 
		 CurrIf ++, CurrEntry ++) {

		auto_ptr<NVDataItem> SubItem (new NVDataItem(NCI_TAG));

		TransString[0] = '\0';

		if (Status != NO_ERROR) {
			delete IfTable;
			return ERROR_SUCCESS;
		}
#if 0
		if (CurrEntry.dwPhysAddrLen < 1)
			continue;
#endif
		char * IfTypeName;
		switch (CurrEntry->dwType) {
		case MIB_IF_TYPE_ETHERNET:
			IfTypeName = "Ethernet 802.3";
			break;

		case MIB_IF_TYPE_TOKENRING:
			IfTypeName = "Token Ring 802.5";
			break;

		case MIB_IF_TYPE_FDDI:
			IfTypeName = "Fiber Distributed Data Interface (FDDI)";
			break;

		case MIB_IF_TYPE_PPP:
			IfTypeName = "PPP";
			break;

		case MIB_IF_TYPE_SLIP:
			IfTypeName = "SLIP";
			break;

		default:
			IfTypeName = "Unknown";
//			continue;
		}

		SubItem->AddNVItem("InterfaceType", IfTypeName);
		
		//if (wcslen(IfTable->Adapter[CurrIf].Name) > 0) {
		//	SubItem->AddNVItem("SysName", W2A(IfTable->Adapter[CurrIf].Name));
		//}

		if (CurrEntry->wszName != NULL && wcslen(CurrEntry->wszName) > 0) {
			SubItem->AddNVItem("Description", CurrEntry->wszName);
		}
		else if (strlen((const char *) CurrEntry->bDescr) > 0) {
			SubItem->AddNVItem("Description", (const char *) CurrEntry->bDescr);
		}

		//_ASSERT (CurrIfTableEntry.dwPhysAddrLen == 6);

		if (CurrEntry->bPhysAddr[0] == 0
		    && CurrEntry->bPhysAddr[1] == 0
		    && CurrEntry->bPhysAddr[2] == 0
		    && CurrEntry->bPhysAddr[3] == 0
		    && CurrEntry->bPhysAddr[4] == 0
			&& CurrEntry->bPhysAddr[5] == 0) {

			continue;
		}

		sprintf (TransString,"%02X:%02X:%02X:%02X:%02X:%02X",
					CurrEntry->bPhysAddr[0],
					CurrEntry->bPhysAddr[1],
					CurrEntry->bPhysAddr[2],
					CurrEntry->bPhysAddr[3],
					CurrEntry->bPhysAddr[4],
					CurrEntry->bPhysAddr[5]);

		SubItem->AddNVItem("MACAddress", TransString);


		string IPAddrList;
		
		long CurrIPIndex;
		MIB_IPADDRROW * CurrIPAddrInfo;
		long FoundIP = 0;

		for (CurrIPIndex = 0, CurrIPAddrInfo = IPAddrTable->table; 
			 CurrIPIndex < IPAddrTable->dwNumEntries; 
			 CurrIPIndex ++, CurrIPAddrInfo ++) {

			if (IPAddrTable->table[CurrIPIndex].dwIndex == CurrEntry->dwIndex) {
				FoundIP ++;
				if (FoundIP > 1)
					IPAddrList.append(",");
				else {
					GetIPAddrString (CurrIPAddrInfo->dwMask, IPString);
					SubItem->AddNVItem("IPSubNet", IPString);
				}
					

				GetIPAddrString(CurrIPAddrInfo->dwAddr, IPString);
				IPAddrList.append(IPString);
			}
		}

		SubItem->AddNVItem("IPAddress", IPAddrList.c_str());

		DataItems->AddSubItem(SubItem.release());
	}

	delete IfTable;
	delete IPAddrTable;

	// WinSetupEnumerateDevClass((GUID) GUID_DEVCLASS_NET, NCI_TAG, DataItems, NULL);

	return ERROR_SUCCESS;
}