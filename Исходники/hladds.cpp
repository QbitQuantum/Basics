/*
read the profile :
fedExeNameChar;
fomNameChar;
fedNameChar
*/
void Hla::readIn( )
{
	
	TCHAR fedNameChar[256];
	TCHAR userNameChar[256];
	TCHAR fedExeNameChar[256];
	TCHAR fomNameChar[256];
	TCHAR crcAddressChar[256];
	TCHAR crcPortChar[256];
	TCHAR syncPointChar[256];
		
	GetPrivateProfileString(L"GENERAL", L"FEDEXENAME", L"NO TEXT", fedExeNameChar, 256, Path);
	GetPrivateProfileString(L"GENERAL", L"FOMNAME", L"NO TEXT", fomNameChar, 256, Path);
	GetPrivateProfileString(L"GENERAL", L"CRC", L"NO TEXT", crcAddressChar, 256, Path);
	GetPrivateProfileString(L"GENERAL", L"CRC_PORT", L"NO TEXT", crcPortChar, 256, Path);
	GetPrivateProfileStringW(L"pub", L"FedName", L"NO TEXT", fedNameChar, 256, Path);
  //GetPrivateProfileStringW(L"sub", L"FedName", L"NO TEXT", fedNameChar, 256, Path);
	
	if (L"NO TEXT" == fedExeNameChar)
	{
		wcout << L"配置文件错误" << endl;
		wcout << L"联邦名称错误" << endl;
		system("pause");
	}
	if (L"NO TEXT" == fomNameChar)
	{
		wcout << L"配置文件错误" << endl;
		wcout << L"Fom表名称错误" << endl;
		system("pause");
	}
	if (L"NO TEXT" == crcAddressChar)
	{
		wcout << L"配置文件错误" << endl;
		wcout << L"crc地址错误" << endl;
		system("pause");
	}
	if (L"NO TEXT" == crcPortChar)
	{
		wcout << L"配置文件错误" << endl;
		wcout << L"crc端口错误" << endl;
		system("pause");
	}
	if (L"NO TEXT" == fedNameChar)
	{
		wcout << L"配置文件错误" << endl;
		wcout << L"fed名称错误" << endl;
		system("pause");
	}
	
	fedExeName_ = fedExeNameChar;
	fomName_    = fomNameChar;
	crcAddress_ = crcAddressChar;
	crcPort_    = crcPortChar;
	fedName_    = fedNameChar;
	
}