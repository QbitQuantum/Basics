DWORD request_core_machine_id(Remote* pRemote, Packet* pPacket)
{
	DWORD res = ERROR_SUCCESS;
	Packet* pResponse = packet_create_response(pPacket);

	if (pResponse)
	{
		wchar_t buffer[MAX_PATH];
		if (GetSystemDirectory(buffer, MAX_PATH) != 0)
		{
			wchar_t computerName[MAX_PATH];
			DWORD computerNameSize = MAX_PATH;
			DWORD serialNumber;
			wchar_t* backslash = wcschr(buffer, L'\\');
			*(backslash + 1) = L'\0';

			GetVolumeInformation(buffer, NULL, 0, &serialNumber, NULL, 0, NULL, 0);

			GetComputerName(computerName, &computerNameSize);

			_snwprintf_s(buffer, MAX_PATH, MAX_PATH - 1, L"%04x-%04x:%s", HIWORD(serialNumber), LOWORD(serialNumber), computerName);
			packet_add_tlv_wstring(pResponse, TLV_TYPE_MACHINE_ID, buffer);
			dprintf("[CORE] sending machine id: %S", buffer);
		}

		packet_transmit_response(res, pRemote, pResponse);
	}

	return ERROR_SUCCESS;
}