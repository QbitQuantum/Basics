void TelnetReader::GetTelnetIPS()
{	
	telnetIPList_Aft.clear();
	telnetIPList_Arp.clear();

	if (path.empty())
	{
		return;
	}

	int i;  
	int iPos = 0;  
	int iMaxCount;
	char chSectionNames[MAX_ALLSECTIONS] = {0}; //存放所有提出来的字符串
	char chSection[MAX_SECTION] = {0}; //存放一个段名
	string filename = path + "\\telnet.ini";

	DWORD dw = GetPrivateProfileSectionNamesA(chSectionNames, MAX_ALLSECTIONS, filename.c_str());
	if (dw == 0)
	{
		return;
	}

	//以下循环，截断到两个连续的0
	for (i = 0; i < MAX_ALLSECTIONS; i++)
	{
		if (chSectionNames[i] == 0)
			if (0 == chSectionNames[i+1])
				break;
	}

	iMaxCount = i + 1; 

	//得到telnet.ini中所有的section
	list<string> sectionList;
	for (i = 0; i < iMaxCount; i++)
	{
		chSection[iPos++] = chSectionNames[i];
		if (chSectionNames[i] == 0)
		{   
			sectionList.push_back((string)chSection);
			memset(chSection, 0, MAX_SECTION);
			iPos=0;
		}
	}

	char IniBuff[50];
	for (list<string>::iterator iter = sectionList.begin(); iter != sectionList.end(); ++iter)
	{
		ZeroMemory(IniBuff, 50);
		GetPrivateProfileStringA((*iter).c_str(), "HostIp", "", IniBuff, 50, filename.c_str());
		string hostip = IniBuff;
		
		ZeroMemory(IniBuff, 50);
		GetPrivateProfileStringA((*iter).c_str(), "indicatorIndex", "", IniBuff, 50, filename.c_str());
		string indicatorIndex = IniBuff;
		if (indicatorIndex == "20000")
		{
			telnetIPList_Aft.push_back(hostip);
		}
		else if(indicatorIndex == "20001")
		{
			telnetIPList_Arp.push_back(hostip);
		}
	}

	////测试telnetIPList_Aft及telnetIPList_Arp
	//for (list<string>::iterator iter = telnetIPList_Aft.begin(); iter != telnetIPList_Aft.end(); ++iter)
	//{
	//	cout<<"telnet ip (by aft): "<<*iter<<endl;
	//}
	//for (list<string>::iterator iter = telnetIPList_Arp.begin(); iter != telnetIPList_Arp.end(); ++iter)
	//{
	//	cout<<"telnet ip (by arp): "<<*iter<<endl;
	//}
}