/**
 * Finds the associated Win32_NetworkAdapterConfiguration for Win32_NetworkAdapter adapterObj.
 * Iterates through the IP addresses associated with the adapter and chooses the highest
 * priority IP address (according to EnumIPSelectionPriority) as the adapter address
 * which is used to populate adapter->userData->ipAddr.
 * If two addresses have the same highest priority, then the first one seen is chosen.
 */
void readIpAddresses(IWbemServices *pNamespace, IWbemClassObject *adapterObj, SFLAdaptor *adaptor)
{
	IEnumWbemClassObject *configEnum;
	HRESULT hr = associatorsOf(pNamespace, adapterObj,
							   L"Win32_NetworkAdapterSetting",
							   L"Win32_NetworkAdapterConfiguration",
							   L"Setting", &configEnum);
	if (SUCCEEDED(hr)) {
		IWbemClassObject *configObj;
		ULONG configCount;
		hr = configEnum->Next(WBEM_INFINITE, 1, &configObj, &configCount);
		if (SUCCEEDED(hr) && configCount == 1) {
			VARIANT addresses;
			hr = configObj->Get(L"IPAddress", 0, &addresses, 0, 0);
			if (WBEM_S_NO_ERROR == hr && addresses.vt == (VT_ARRAY |VT_BSTR))  {
				SAFEARRAY *sa = V_ARRAY(&addresses);
				LONG lstart, lend;
				hr = SafeArrayGetLBound(sa, 1, &lstart);
				hr = SafeArrayGetUBound(sa, 1, &lend);
				BSTR *pbstr;
				hr = SafeArrayAccessData(sa, (void HUGEP **)&pbstr);
				if (SUCCEEDED(hr)) {
					HSPAdaptorNIO *nioState = (HSPAdaptorNIO *)adaptor->userData;
					for (LONG idx=lstart; idx <= lend; idx++) {		
						PCWSTR addrStr = pbstr[idx];
						IN_ADDR in_addr = {0};
						LPCWSTR terminator;
						LONG result = RtlIpv4StringToAddressW(addrStr, TRUE, &terminator, &in_addr);
						if (NO_ERROR == result) {
							SFLAddress addrv4;
							addrv4.type = SFLADDRESSTYPE_IP_V4;
							addrv4.address.ip_v4.addr =  in_addr.S_un.S_addr;
							EnumIPSelectionPriority ipPriority = agentAddressPriority(&addrv4);
							if (ipPriority > nioState->ipPriority) {
								nioState->ipPriority = ipPriority;
								nioState->ipAddr = addrv4;
							}
						} else {
							IN6_ADDR in6_addr = {0};
							result = RtlIpv6StringToAddressW(addrStr, &terminator, &in6_addr);
							if (NO_ERROR == result) {
								SFLAddress addrv6;
								addrv6.type = SFLADDRESSTYPE_IP_V6;
								memcpy(addrv6.address.ip_v6.addr, in_addr6.u.Byte, sizeof(in6_addr.u.Byte));
								EnumIPSelectionPriority ipPriority = agentAddressPriority(&addrv6);
								if (ipPriority > nioState->ipPriority) {
									nioState->ipPriority = ipPriority;
									nioState->ipAddr = addrv6;
								}
							}
						}
					}
					SafeArrayUnaccessData(sa);
				}
			}
			VariantClear(&addresses);
			configObj->Release();
		}
		configEnum->Release();
	}
}