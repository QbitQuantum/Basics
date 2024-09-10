//通过SNMP(简单网络访问协议)
bool GetMacAddressBySNMP(std::string &mac_address)
{
	bool ret = false;
	WSADATA winsock_data;
	if (WSAStartup(MAKEWORD(2, 0), &winsock_data) != 0) 
		return false;

	// Load the SNMP dll and get the addresses of the functions necessary
	const HINSTANCE m_dll = LoadLibrary(L"inetmib1.dll");
	if (m_dll < (HINSTANCE) HINSTANCE_ERROR)
		return false;

	const PFNSNMPEXTENSIONINIT f_SnmpExtensionInit = (PFNSNMPEXTENSIONINIT) GetProcAddress(m_dll, "SnmpExtensionInit");
//	const PFNSNMPEXTENSIONINITEX f_SnmpExtensionInitEx = (PFNSNMPEXTENSIONINITEX) GetProcAddress(m_dll, "SnmpExtensionInitEx");
 	const PFNSNMPEXTENSIONQUERY f_SnmpExtensionQuery = (PFNSNMPEXTENSIONQUERY) GetProcAddress(m_dll, "SnmpExtensionQuery");
// 	const PFNSNMPEXTENSIONTRAP f_SnmpExtensionTrap = (PFNSNMPEXTENSIONTRAP) GetProcAddress(m_dll, "SnmpExtensionTrap");
	HANDLE poll_for_trap_event;
	AsnObjectIdentifier supported_view;
	f_SnmpExtensionInit(GetTickCount(), &poll_for_trap_event, &supported_view);

	// Initialize the variable list to be retrieved by f_SnmpExtensionQuery
	const AsnObjectIdentifier MIB_NULL = { 0, 0 };

	RFC1157VarBind var_bind[2];
	var_bind[0].name = MIB_NULL;
	var_bind[1].name = MIB_NULL;

	RFC1157VarBindList var_bind_list;
	var_bind_list.list = var_bind;

	UINT OID_ifEntryType[] = { 1, 3, 6, 1, 2, 1, 2, 2, 1, 3 };
	UINT OID_ifEntryNum[] = { 1, 3, 6, 1, 2, 1, 2, 1 };
	UINT OID_ipMACEntAddr[] = { 1, 3, 6, 1, 2, 1, 2, 2, 1, 6 };
	AsnObjectIdentifier MIB_ifMACEntAddr = { sizeof(OID_ipMACEntAddr) / sizeof(UINT), OID_ipMACEntAddr };
	AsnObjectIdentifier MIB_ifEntryType = { sizeof(OID_ifEntryType) / sizeof(UINT), OID_ifEntryType };
	AsnObjectIdentifier MIB_ifEntryNum = { sizeof(OID_ifEntryNum) / sizeof(UINT), OID_ifEntryNum };

	// Copy in the OID to find the number of entries in the Inteface table
	var_bind_list.len = 1;        // Only retrieving one item
	SnmpUtilOidCpy(&var_bind[0].name, &MIB_ifEntryNum);
	AsnInteger errorStatus;
	AsnInteger errorIndex;
	f_SnmpExtensionQuery(ASN_RFC1157_GETNEXTREQUEST, &var_bind_list, &errorStatus, &errorIndex);
	var_bind_list.len = 2;

	// Copy in the OID of ifType, the type of interface
	SnmpUtilOidCpy(&var_bind[0].name, &MIB_ifEntryType);

	// Copy in the OID of ifPhysAddress, the address
	SnmpUtilOidCpy(&var_bind[1].name, &MIB_ifMACEntAddr);

	for(int j = 0; j < var_bind[0].value.asnValue.number; j++)
	{
		// Submit the query.  Responses will be loaded into var_bind_list.
		// We can expect this call to succeed a # of times corresponding to the # of adapters reported to be in the system
		if(f_SnmpExtensionQuery(ASN_RFC1157_GETNEXTREQUEST, &var_bind_list, &errorStatus, &errorIndex) == FALSE)
			continue;
		// Confirm that the proper type has been returned
		if(SnmpUtilOidNCmp(&var_bind[0].name, &MIB_ifEntryType, MIB_ifEntryType.idLength) != 0)
			continue;
		// Type 6 describes ethernet interfaces
		if(var_bind[0].value.asnValue.number != 6) 
			continue;
		// Confirm that we have an address here
		if(SnmpUtilOidNCmp(&var_bind[1].name, &MIB_ifMACEntAddr, MIB_ifMACEntAddr.idLength) != 0)
			continue;
		if(var_bind[1].value.asnValue.address.stream == NULL)
			continue;
		// Ignore all dial-up networking adapters
		if ((var_bind[1].value.asnValue.address.stream[0] == 0x44)
			&& (var_bind[1].value.asnValue.address.stream[1] == 0x45)
			&& (var_bind[1].value.asnValue.address.stream[2] == 0x53)
			&& (var_bind[1].value.asnValue.address.stream[3] == 0x54)
			&& (var_bind[1].value.asnValue.address.stream[4] == 0x00)) 
			continue;
		// Ignore NULL addresses returned by other network interfaces
		if ((var_bind[1].value.asnValue.address.stream[0] == 0x00)
			&& (var_bind[1].value.asnValue.address.stream[1] == 0x00)
			&& (var_bind[1].value.asnValue.address.stream[2] == 0x00)
			&& (var_bind[1].value.asnValue.address.stream[3] == 0x00)
			&& (var_bind[1].value.asnValue.address.stream[4] == 0x00)
			&& (var_bind[1].value.asnValue.address.stream[5] == 0x00)) 
			continue;

		StringPrintf(mac_address, "%02x-%02x-%02x-%02x-%02x-%02x",
			var_bind[1].value.asnValue.address.stream[0],
			var_bind[1].value.asnValue.address.stream[1],
			var_bind[1].value.asnValue.address.stream[2],
			var_bind[1].value.asnValue.address.stream[3],
			var_bind[1].value.asnValue.address.stream[4],
			var_bind[1].value.asnValue.address.stream[5]);

		ret = true;
		break;
	}

	// Free the bindings
	SnmpUtilVarBindFree(&var_bind[0]);
	SnmpUtilVarBindFree(&var_bind[1]);
	return ret;
}