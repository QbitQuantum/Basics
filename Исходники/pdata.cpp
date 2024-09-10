static cell AMX_NATIVE_CALL get_pdata_string(AMX *amx, cell *params)
{
	int index=params[1];
	CHECK_ENTITY(index);

	int iOffset=params[2];
	CHECK_OFFSET(iOffset);

#if defined( __linux__ )
	iOffset += params[6];
#elif defined( __APPLE__ )
	// Use Linux offset in older plugins
	if (params[0] / sizeof(cell) == 6 || params[7] == CELL_MIN)
		iOffset += params[6];
	else
		iOffset += params[7];
#endif
	edict_t *pEdict = TypeConversion.id_to_edict(index);

	char *szData;
	if (params[5])
	{
		szData = get_pdata<char*>(pEdict, iOffset);
	} else {
		szData = get_pdata_direct<char*>(pEdict, iOffset);
	}

	if (IsBadReadPtr(szData, 1))
	{
		return 0;
	}

	MF_SetAmxString(amx, params[3], szData, params[4]);

	return 1;
}