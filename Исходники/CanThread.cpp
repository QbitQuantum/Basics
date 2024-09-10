DWORD ReadAddrMap(DWORD Addr)
{
	//TCHAR buffer[20];
	DWORD IP;
	wchar_t buildingString[20],UnitString[20];
	LPCTSTR Building,Unit;
	DWORD build_temp,Unit_temp;
	build_temp=(Addr>>22)&(0x3ff);
	Unit_temp=(Addr>>16)&(0x3f);
	ZeroMemory(buildingString,sizeof(buildingString));
	ZeroMemory(UnitString,sizeof(UnitString));
	//_itoa(build_temp,buildingString,10);
	_itow(build_temp,buildingString,10);
	Building=(LPCTSTR)buildingString;
	//_itoa(Unit_temp,UnitString,10);
	_itow(Unit_temp,UnitString,10);
	Unit=(LPCTSTR)UnitString;
	IP=(DWORD)CeGetPrivateProfileInt(Building, Unit, -1, _T("\\UserDev\\SysSet.ini"));
	return IP;
}