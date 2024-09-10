/**
 * Set a filesystem GUID according to the filesystem name
 * We use a static ID for the first 8 bytes, and then roll the lowercase name
 * for the last 8 bytes (eg. exfat => {'e', 'x', 'f', 'a', 't', 'e', 'x', 'f'})
 */
EFI_GUID *
GetFSGuid(VOID)
{
	INTN i, j, k, Len = StrLen(WIDEN(STRINGIFY(DRIVERNAME)));
	static EFI_GUID Guid = { 0xEF1F5EF1, 0xF17E, 0x5857, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
	CHAR16 *FsName = WIDEN(STRINGIFY(DRIVERNAME));
	const CHAR16 *PlusName = L"plus";
    EFI_UNICODE_COLLATION_PROTOCOL *UnicodeCollation;
	UINT8 Data4[12];	/* +4 so that we can also reduce something like "1234567plus" into "1234567+" */
    EFI_STATUS Status = EFI_SUCCESS;

    Status = gBS->LocateProtocol(&gEfiUnicodeCollation2ProtocolGuid, NULL, (VOID**)&UnicodeCollation);
    if (EFI_ERROR(Status) || (UnicodeCollation == NULL))
    {
      Status = gBS->LocateProtocol(&gEfiUnicodeCollationProtocolGuid, NULL, (VOID**)&UnicodeCollation);
    }

    if (EFI_ERROR(Status) || (UnicodeCollation == NULL))
    {
      Print(L"ERROR: Could not open unicode collation protocol\n");

      return NULL;
    }

	UnicodeCollation->StrLwr(UnicodeCollation, FsName);

	for (i = 0, j = 0, k = 0; j < ARRAYSIZE(Data4); i = (i+1)%Len, j++) {
		/* Convert any 'plus' that is part of the name to '+' */
		if (FsName[i] == PlusName[k]) {
			if (++k == 4) {
				k = 0;
				j -= 3;
				Data4[j] = (UINT8) '+';
			} else {
				Data4[j] = FsName[i];
			}
		} else {
			k = 0;
			Data4[j] = FsName[i];
		}
	}

    if (FsName != NULL)
    {
        FreePool(FsName);
        FsName = NULL;
    }

        
    CopyMem(Guid.Data4, Data4, 8);

	return &Guid;
}