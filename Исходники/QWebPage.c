//增加一条记录，并同步显示
//Addr不能为0，Name可以为空，name为空，则不修改name
static void AddOneDevice(u8 Addr,u8 *Name)
{
	u8 i;
	u8 Len=0;
	u16 NameChk;

	if(Name!=NULL) Len=strlen((void *)Name);
	if(Len>=DEVICE_NAME_MAX_LEN) Len=DEVICE_NAME_MAX_LEN-1;
	NameChk=MakeHash33(Name,Len);

	for(i=0;i<DEVICE_INFO_MAX_CLIENT_RECORD;i++)
	{
		//对比地址或名字，如果地址相等，直接修改名字，如果名字相同，则修改地址。
		if((gpQwpVar->ClientRecord[i].Addr==Addr)||((gpQwpVar->ClientRecord[i].Addr!=0)&&(gpQwpVar->ClientRecord[i].NameChk==NameChk)))
		{//修改现成的
			gpQwpVar->ClientRecord[i].Addr=Addr;
			
			if((Name!=NULL)&&(gpQwpVar->ClientRecord[i].NameChk!=NameChk))//修改名字
			{
				MemCpy(gpQwpVar->ClientRecord[i].Name,Name,Len);
				gpQwpVar->ClientRecord[i].Name[Len]=0;
			}

			if(gpQwpVar->ClientRecord[i].IsHiLight==TRUE)
				DrawDeviceInfo(gpQwpVar->ClientRecord[i].DispIdx,Addr,gpQwpVar->ClientRecord[i].Name,HighLightDisp);
			else
				DrawDeviceInfo(gpQwpVar->ClientRecord[i].DispIdx,Addr,gpQwpVar->ClientRecord[i].Name,NormalDisp);
			break;
		}
	}

	if(i==DEVICE_INFO_MAX_CLIENT_RECORD)//not found ,add new one.
	{//建新的
		for(i=0;i<DEVICE_INFO_MAX_CLIENT_RECORD;i++)
			if(gpQwpVar->ClientRecord[i].Addr==0)
			{
				gpQwpVar->ClientRecord[i].Addr=Addr;
				MemCpy(gpQwpVar->ClientRecord[i].Name,Name,Len);
				gpQwpVar->ClientRecord[i].Name[Len]=0;
				gpQwpVar->ClientRecord[i].NameChk=MakeHash33(gpQwpVar->ClientRecord[i].Name,Len);
				gpQwpVar->ClientRecord[i].DispIdx=++gpQwpVar->NowDispNum;
				DrawDeviceInfo(gpQwpVar->ClientRecord[i].DispIdx,Addr,gpQwpVar->ClientRecord[i].Name,NormalDisp);
				break;
			}
	}	

	DrawState();//更新下状态
}