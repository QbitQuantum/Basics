bool HookImportAddrTable(BYTE *base, const char *func, DWORD hookfunc, char *err, size_t maxlength)
{
	IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER *)base;
	if (dos->e_magic != IMAGE_DOS_SIGNATURE)
	{
		UTIL_Format(err, maxlength, "%s", "Could not detect valid DOS signature");
		return false;
	}

	IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)(base + dos->e_lfanew);
	if (nt->Signature != IMAGE_NT_SIGNATURE)
	{
		UTIL_Format(err, maxlength, "%s", "Could not detect valid NT signature");
		return false;
	}

	IMAGE_IMPORT_DESCRIPTOR *desc = 
		(IMAGE_IMPORT_DESCRIPTOR *)
		(base + nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	if (base == (BYTE *)desc)
	{
		UTIL_Format(err, maxlength, "%s", "Could not find IAT");
		return false;
	}

	bool entryFound = false;
	while (desc->Name)
	{
		if (desc->FirstThunk != 0)
		{
			IMAGE_THUNK_DATA *data = (IMAGE_THUNK_DATA *)(base + desc->OriginalFirstThunk);
			DWORD *iat = (DWORD *)(base + desc->FirstThunk);
			while (data->u1.Function)
			{
				if ((data->u1.Ordinal & IMAGE_ORDINAL_FLAG32) != IMAGE_ORDINAL_FLAG32)
				{
					IMAGE_IMPORT_BY_NAME *import = (IMAGE_IMPORT_BY_NAME *)(base + data->u1.AddressOfData);
					if (strcmp((char *)import->Name, func) == 0)
					{
						DWORD oldprot, oldprot2;
						VirtualProtect(iat, 4, PAGE_READWRITE, &oldprot);
						*iat = hookfunc;
						VirtualProtect(iat, 4, oldprot, &oldprot2);
						entryFound = true;
					}
				}
				data++;
				iat++;
			}
		}
		desc++;
	}

	if (!entryFound)
	{
		UTIL_Format(err, maxlength, "Could not find IAT entry for %s", func);
		return false;
	}

	return true;
}