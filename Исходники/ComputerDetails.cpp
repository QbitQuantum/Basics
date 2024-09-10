//功能：	枚举机器上的所有的物理网卡(不包括虚拟网卡)
//参数：	NIC结构体的列表，调用成功包含所有的物理网卡的相关系统
//返回值：	调用成功返回TRUE，否则返回FALSE
//调用成功后必须调用FreeNicListBuffer释放内存
 BOOL  NetworkInterfaces(NICLIST **Niclist)
{
	if (NULL==Niclist)
	{
		return FALSE;
	}
	else
	{
		*Niclist=NULL;
	}

	HDEVINFO hDevInfo=INVALID_HANDLE_VALUE;

	//if (INVALID_HANDLE_VALUE == (hDevInfo =SetupDiGetClassDevs(&GUID_NDIS_LAN_CLASS/*NULL*/,NULL,NULL,	DIGCF_DEVICEINTERFACE/*DIGCF_PRESENT |DIGCF_ALLCLASSES*/))) 
	if (INVALID_HANDLE_VALUE == (hDevInfo =SetupDiGetClassDevs(&GUID_NDIS_LAN_CLASS, NULL, NULL, DIGCF_DEVICEINTERFACE))) 
	{ 
		return FALSE; 
	} 

	Garbage DevListGC(hDevInfo);

	DWORD	i		=0, 
		Status	=0,
		Problem	=0;
	NIC		CurNic;

	SP_DEVINFO_DATA DeviceInfoData	={sizeof(SP_DEVINFO_DATA)}; 

	TCHAR			Buffer[MY_BUFFER_SIZE]	={0};
	DWORD			Length			=sizeof(Buffer);

	std::list<NIC> nics_list;

	for (i=0;SetupDiEnumDeviceInfo(hDevInfo,i,&DeviceInfoData);i++) 
	{ 
		if (CM_Get_DevNode_Status(&Status, &Problem, DeviceInfoData.DevInst,0) == CR_SUCCESS)
		{
			if ( ((Status & DN_NO_SHOW_IN_DM)==0)&&(!IsClassHidden(&DeviceInfoData.ClassGuid)) )
			//if ( ((Status & DN_NO_SHOW_IN_DM)==0) )
			{
				CurNic.m_dwId=i;

				if (SetupDiGetDeviceRegistryProperty(hDevInfo,   
					&DeviceInfoData, SPDRP_DEVICEDESC, NULL,(PBYTE)Buffer, Length, &Length))   
				{   
					Buffer[Length]=TEXT('\0');
					//CurNic.m_strDevDesc=Buffer;
					_tcscpy(CurNic.m_chDevDesc,Buffer);
					Length=sizeof(Buffer);
				}
				else
				{
					//CurNic.m_strDevDesc=TEXT("Nic without description");
					_tcscpy(CurNic.m_chDevDesc,TEXT("Nic without description"));
				}

				CurNic.m_bDisabled=(Status & DN_HAS_PROBLEM) && (CM_PROB_DISABLED == Problem);
				CurNic.m_dwNicType=0;
				//CurNic.m_strDevGuid.clear();
				CurNic.m_chDevGuid[0]=TEXT('\0');

				DWORD dwSizeRequired = 0;
				TCHAR szPnpInstanceId[MY_BUFFER_SIZE+1];

				if (SetupDiGetDeviceInstanceId(hDevInfo, &DeviceInfoData, 
					szPnpInstanceId, MY_BUFFER_SIZE, &dwSizeRequired))
				{
					std::list<TString>	GuidList;
					int					iMedia		=0;
					if (GetNicGuid(szPnpInstanceId,GuidList)&&(!GuidList.empty()))
					{
						//CurNic.m_strDevGuid=GuidList.front();
						_tcscpy(CurNic.m_chDevGuid,GuidList.front().c_str());

						if ((iMedia=GetNicMediaType(GuidList.front()))>0)
						{
							CurNic.m_dwNicType=iMedia;
						}
					}

				}

				if (IsPhysicalNic(/*CurNic.m_strDevGuid.c_str()*/CurNic.m_chDevGuid))
				{
					//TString strDevGuid=CurNic.m_chDevGuid;
					//_tcscpy(CurNic.m_chDevGuid,strDevGuid.substr(1,36).c_str());//去掉GUID的大括号

					nics_list.push_back(CurNic);
				}

			}//if
		}//if
	} //for


	if (nics_list.size()!=0)
	{
		*Niclist=new NICLIST;
		NICLIST *lpTemp=*Niclist;
		lpTemp->dwCount	=nics_list.size();
		lpTemp->lpNics		=new NIC[lpTemp->dwCount];
		int k=0;
		for (std::list<NIC>::iterator i=nics_list.begin();i!=nics_list.end();++i,++k)
		{
			lpTemp->lpNics[k].m_bDisabled	=i->m_bDisabled;
			lpTemp->lpNics[k].m_dwId		=i->m_dwId;
			lpTemp->lpNics[k].m_dwNicType	=i->m_dwNicType;
			_tcscpy(lpTemp->lpNics[k].m_chDevDesc,i->m_chDevDesc);
			_tcscpy(lpTemp->lpNics[k].m_chDevGuid,i->m_chDevGuid);
		}
		return TRUE;
	}
	else
	{
		*Niclist=NULL;
		return FALSE;
	}
}