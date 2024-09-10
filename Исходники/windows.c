static int Lget_nameservers(lua_State *L) {
	char stack_buffer[1024]; // stack allocated buffer
	IP4_ARRAY* ips = (IP4_ARRAY*) stack_buffer;
	DWORD len = sizeof(stack_buffer);
	DNS_STATUS status;

	status = DnsQueryConfig(DnsConfigDnsServerList, FALSE, NULL, NULL, ips, &len);
	if (status == 0) {
		DWORD i;
		lua_createtable(L, ips->AddrCount, 0);
		for (i = 0; i < ips->AddrCount; i++) {
			DWORD ip = ips->AddrArray[i];
			char ip_str[16] = "";
			sprintf_s(ip_str, sizeof(ip_str), "%d.%d.%d.%d", (ip >> 0) & 255, (ip >> 8) & 255, (ip >> 16) & 255, (ip >> 24) & 255);
			lua_pushstring(L, ip_str);
			lua_rawseti(L, -2, i+1);
		}
		return 1;
	} else {