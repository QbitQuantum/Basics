EFI_STATUS
find_boot_option(EFI_DEVICE_PATH *dp, CHAR16 *filename, CHAR16 *label,
		CHAR16 *arguments, UINT16 *optnum)
{
	int size = sizeof(UINT32) + sizeof (UINT16) +
		StrLen(label)*2 + 2 + DevicePathSize(dp) +
		StrLen(arguments) * 2 + 2;

	CHAR8 *data = AllocateZeroPool(size);
	if (!data)
		return EFI_OUT_OF_RESOURCES;
	CHAR8 *cursor = data;
	*(UINT32 *)cursor = LOAD_OPTION_ACTIVE;
	cursor += sizeof (UINT32);
	*(UINT16 *)cursor = DevicePathSize(dp);
	cursor += sizeof (UINT16);
	StrCpy((CHAR16 *)cursor, label);
	cursor += StrLen(label)*2 + 2;
	CopyMem(cursor, dp, DevicePathSize(dp));
	cursor += DevicePathSize(dp);
	StrCpy((CHAR16 *)cursor, arguments);

	int i = 0;
	CHAR16 varname[] = L"Boot0000";
	CHAR16 hexmap[] = L"0123456789ABCDEF";
	EFI_GUID global = EFI_GLOBAL_VARIABLE;
	EFI_STATUS rc;

	CHAR8 *candidate = AllocateZeroPool(size);
	if (!candidate) {
		FreePool(data);
		return EFI_OUT_OF_RESOURCES;
	}

	for(i = 0; i < nbootorder && i < 0x10000; i++) {
		varname[4] = hexmap[(bootorder[i] & 0xf000) >> 12];
		varname[5] = hexmap[(bootorder[i] & 0x0f00) >> 8];
		varname[6] = hexmap[(bootorder[i] & 0x00f0) >> 4];
		varname[7] = hexmap[(bootorder[i] & 0x000f) >> 0];

		UINTN candidate_size = size;
		rc = uefi_call_wrapper(RT->GetVariable, 5, varname, &global,
					NULL, &candidate_size, candidate);
		if (EFI_ERROR(rc))
			continue;

		if (candidate_size != size)
			continue;

		if (CompareMem(candidate, data, size))
			continue;

		/* at this point, we have duplicate data. */
		*optnum = i;
		FreePool(candidate);
		FreePool(data);
		return EFI_SUCCESS;
	}
	FreePool(candidate);
	FreePool(data);
	return EFI_NOT_FOUND;
}