void XFileFinder::GetDriverList(XString8Array &drivers, XString8Array &names)
{
	int drives=GetLogicalDrives();
	int nums=0;
	drives>>=2;
	XTCHAR disk[]="C:\\";
	XString8 strName="(C:)";
	while(drives)
	{
		if(drives&0x01)
		{
//			UINT type=GetDriveType(disk);
			UINT type=GetDriveTypeA(disk);
			XTCHAR buf[64];
			DWORD s;
//			::GetVolumeInformation(disk,buf,64,&s,&s,&s,XNULL,0);
			::GetVolumeInformationA(disk,buf,64,&s,&s,&s,XNULL,0);
			if(type!=DRIVE_CDROM)
			{
				drivers.Add(disk);
				XString8 str;
				if((type==DRIVE_REMOVABLE)&&buf[0]==0)
				{

					str=XResource::LoadWString(XIDS_REMOVEBLEDISK);
						//"���ƶ���";
				}
				else str=buf;
				strName[1]=disk[0];
				str+=strName;
				names.Add(str);
			}
		}
		disk[0]++;
		drives>>=1;
	}

}