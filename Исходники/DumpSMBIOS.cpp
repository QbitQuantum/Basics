int _tmain(int argc, _TCHAR* argv[])
{
	DWORD needBufferSize = 0;
	// the seqence just for x86, but don't worry we know SMBIOS/DMI only exist on x86 platform
	const BYTE byteSignature[] = { 'B', 'M', 'S', 'R' };
	const DWORD Signature = *((DWORD*)byteSignature);
	LPBYTE pBuff = NULL;

	needBufferSize = GetSystemFirmwareTable(Signature, 0, NULL, 0);

	_tprintf(TEXT("We need prepare %d bytes for recevie SMBIOS/DMI Table\n"), needBufferSize);
	pBuff = (LPBYTE) malloc(needBufferSize);
	if (pBuff)
	{
		GetSystemFirmwareTable(Signature, 0, pBuff, needBufferSize);

		const PRawSMBIOSData pDMIData = (PRawSMBIOSData)pBuff;
		_tprintf(TEXT("SMBIOS version:%d.%d\n"), pDMIData->SMBIOSMajorVersion, pDMIData->SMBIOSMinorVersion);
		_tprintf(TEXT("DMI Revision:%x\n"), pDMIData->DmiRevision);
		_tprintf(TEXT("Total length: %d\n"), pDMIData->Length);
		_tprintf(TEXT("DMI at address %x\n"), (DWORD)((PBYTE)&pDMIData->SMBIOSTableData));

		DumpSMBIOSStruct(&(pDMIData->SMBIOSTableData), pDMIData->Length);
	}
	else
		_tprintf(TEXT("Can not allocate memory for recevice SMBIOS/DMI table\n"));

	if (pBuff)
		free(pBuff);
	return 0;
}