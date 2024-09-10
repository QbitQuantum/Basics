LONG CDevControl::StartUpgrade(LONG lLoginID, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser)
{
    if (m_pManager->IsDeviceValid((afk_device_s*)lLoginID) < 0)
    {
		m_pManager->SetLastError(NET_INVALID_HANDLE);
        return 0;
    }

	if (!pchFileName)
	{
		m_pManager->SetLastError(NET_ILLEGAL_PARAM);
		return 0;
	}

    afk_device_s *device = (afk_device_s*)lLoginID;

    st_Upgrade_Info* pUI = new st_Upgrade_Info;
	if (!pUI)
	{
		m_pManager->SetLastError(NET_SYSTEM_ERROR);
		return 0;
	}

	afk_channel_s *pchannel = 0;
	afk_upgrade_channel_param_s upgradechannel = {0};

	FILE *file = fopen(pchFileName, "rb");
    if (file)
    {
        fpos_t pos;
        fseek(file, 0, SEEK_END);
        fgetpos(file, &pos);
#ifdef WIN32
        upgradechannel.size = pos;
#else	//linux
        upgradechannel.size = pos.__pos;
#endif
    }
    else
    {
		delete pUI;
		m_pManager->SetLastError(NET_ERROR);
        return 0;
    }

	//判断升级文件类型，应用程序也应该做这部分工作，以免升错文件
	//...新协议中不区分升级类型，升级类型由设备去判断。升级包的头两个字节("DH"和"PK")
	int ret = 0;
	int nUpgradeFlag = 0;
	char tmpbuf[3];
	memset(tmpbuf, 0, 3);
	fseek(file, 0, SEEK_SET);
	fread(tmpbuf, 1, 2, file);
	if ((tmpbuf[0] == 'D' && tmpbuf[1] == 'H') || (tmpbuf[0] == 'P' && tmpbuf[1] == 'K'))
	{
		nUpgradeFlag = 1;	//bios
	}
	else if (tmpbuf[0] == 'U')	
	{
		nUpgradeFlag = 2;	//Web
	}
	else if (tmpbuf[0] == (char)0xC0 && tmpbuf[1] == (char)0x80)
	{
		nUpgradeFlag = 3;//boot
		if (upgradechannel.size <= 1202180) 
		{
			 //boot
		}
		else
		{
			//boot and bios
		}
	}
	else
	{
		goto e_clearup;
	}
	fclose(file);
	file = NULL;
	
	upgradechannel.filetype = nUpgradeFlag;
	upgradechannel.type = AFK_CHANNEL_UPLOAD_UPGRADE;

	pUI->pcsLock = new DEVMutex;
	if (!pUI->pcsLock)
	{
		m_pManager->SetLastError(NET_SYSTEM_ERROR);
		goto e_clearup;
	}
	
	ret = CreateEventEx(pUI->hRecEvent, TRUE, FALSE);
	if (ret < 0)
	{
		m_pManager->SetLastError(NET_SYSTEM_ERROR);
		goto e_clearup;
	}
	
	InterlockedSetEx(&pUI->life, 1);

	pUI->device = device;
	pUI->channel = 0;
	pUI->cbUpgrade = cbUpgrade;
	pUI->dwUser = dwUser;

    upgradechannel.base.func = UpgradeFunc; 
    upgradechannel.base.udata = pUI;
    strcpy(upgradechannel.filename, pchFileName);

    pchannel = (afk_channel_s*)device->open_channel(device, 
        AFK_CHANNEL_TYPE_UPGRADE, &upgradechannel);
    if (pchannel)
    {
		DWORD dwRet = WaitForSingleObjectEx(pUI->hRecEvent, 10*WAIT_TIME);
        ResetEventEx(pUI->hRecEvent);
        if (dwRet == WAIT_OBJECT_0)
        {
            pUI->channel = pchannel;

			m_csUI.Lock();
			m_lstUI.push_back(pUI);
			m_csUI.UnLock();
        }
		else
		{
			goto e_clearup;
		}
    }
	else
	{
		goto e_clearup;
	}

    return (LONG)pchannel;

e_clearup:
	if (file)
	{
		fclose(file);
		file = 0;
	}

	if (pchannel)
	{
		pchannel->close(pchannel);
		pchannel = 0;
	}
	
	if (pUI)
	{
		if (pUI->pcsLock)
		{
			delete pUI->pcsLock;
			pUI->pcsLock = 0;
		}
		
		CloseEventEx(pUI->hRecEvent);
		
		delete pUI;
		pUI = 0;
	}

	return 0;
}