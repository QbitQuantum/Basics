bool MCScreenDC::listprinters(MCStringRef& r_printers)
{
	MCAutoListRef t_list;
	if (!MCListCreateMutable('\n', &t_list))
		return false;

	DWORD t_flags;
	DWORD t_level;
	t_flags = PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS;
	t_level = 4;

	DWORD t_printer_count;
	DWORD t_bytes_needed;
	t_printer_count = 0;
	t_bytes_needed = 0;
	if (EnumPrintersW(t_flags, NULL, t_level, NULL, 0, &t_bytes_needed, &t_printer_count) != 0 || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		MCAutoPointer<byte_t> t_printers;
		if (!MCMemoryNewArray(t_bytes_needed, &t_printers))
			return false;

		if (EnumPrintersW(t_flags, NULL, t_level, (LPBYTE)*t_printers, t_bytes_needed, &t_bytes_needed, &t_printer_count) != 0)
		{
			for(uint4 i = 0; i < t_printer_count; ++i)
			{
				MCAutoStringRef t_printer_name;
				if (!MCStringCreateWithWString(((PRINTER_INFO_4W *)*t_printers)[i] . pPrinterName, &t_printer_name))
					return false;
				if (!MCListAppend(*t_list, *t_printer_name))
					return false;
			}
		}
	}

	return MCListCopyAsString(*t_list, r_printers);
}