JNIEXPORT jobjectArray JNICALL Java_org_krakenapps_winapi_RoutingTable_getRoutingEntries(JNIEnv *env, jobject obj) {
	jclass clzRoutingEntry = (*env)->FindClass(env, "org/krakenapps/winapi/RoutingEntry");
	jobjectArray entries = NULL;
	PMIB_IPFORWARDTABLE pIpForwardTable = NULL;
	ULONG dwSize = 0;
	DWORD error = 0;
	DWORD i;

	pIpForwardTable = (PMIB_IPFORWARDTABLE)malloc(sizeof(MIB_IPFORWARDTABLE));
	if((error = GetIpForwardTable(pIpForwardTable, &dwSize, TRUE)) != NO_ERROR) {
		LPTSTR errorMsg = L"Error in GetIpForwardTable";
		free(pIpForwardTable);

		switch(error) {
			case ERROR_INSUFFICIENT_BUFFER:
				pIpForwardTable = (PMIB_IPFORWARDTABLE)malloc(dwSize);
				if((error = GetIpForwardTable(pIpForwardTable, &dwSize, TRUE)) == NO_ERROR) {
					break;
				}

			case ERROR_INVALID_PARAMETER:
				errorMsg = L"Invalid parameter error in GetIpForwardTable";

			case ERROR_NO_DATA:
				errorMsg = L"No data error in GetIpForwardTable";

			case ERROR_NOT_SUPPORTED:
				errorMsg = L"Not supported error in GetIpForwardTable";

			default:
				fwprintf(stderr, L"%s\n", errorMsg);
				return NULL;
		}
	}

	entries = (*env)->NewObjectArray(env, pIpForwardTable->dwNumEntries, clzRoutingEntry, NULL);
	for(i=0; i<pIpForwardTable->dwNumEntries; i++) {
		(*env)->SetObjectArrayElement(env, entries, i, getForwardRow(env, pIpForwardTable->table[i]));
	}
	free(pIpForwardTable);

	return entries;
}