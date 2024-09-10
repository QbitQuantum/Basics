//BGI 使用0xA表示换行
string WINAPI GetString(PBYTE BufferStart, ULONG& Offset)
{
	ULONG Value = *(PULONG)(BufferStart + Offset);
	Offset += 4;
	WCHAR WideString[1500] = { 0 };
	CHAR UTF8Name[2000] = { 0 };

	ScriptHeader* Header = (ScriptHeader*)BufferStart;
	ULONG HeaderSize = Header->HeaderSize - sizeof(ULONG) + sizeof(ScriptHeader);

	MultiByteToWideChar(GBKMode ? 936 : 932, 0, (CHAR*)(BufferStart + Value + HeaderSize), lstrlenA((CHAR*)(BufferStart + Value + HeaderSize)), WideString, 1500);
	WideCharToMultiByte(CP_UTF8, 0, WideString, lstrlenW(WideString), UTF8Name, 2000, nullptr, nullptr);

#ifndef DUMP_TEXT_ONLY
	return  FixString("\"" + string(UTF8Name) + "\"");
#else
	return  FixString(string(UTF8Name));
#endif
}