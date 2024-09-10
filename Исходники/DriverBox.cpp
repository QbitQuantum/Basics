/////////////////////////////////////////////////////////////////////////////
// CDriverBox message handlers
//创建控件时调用，该函数中查找所有可用的驱动器
//并将其名称保存到列表字符列表中和加入到显示列表中
void CDriverBox::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CComboBox::PreSubclassWindow();
    DWORD drives=GetLogicalDrives();
	int nums=0;	
	drives>>=2;
	char disk[]=_T("c:\\");	
	while(drives)
	{
		if(drives&0x01)
		{						
			UINT type=GetDriveType(disk);
			if(type==DRIVE_FIXED||type==DRIVE_REMOTE)
			{
				disk[2]=0;
				AddString(disk);
				m_drvList.AddTail(disk);
				disk[2]='\\';
			}
		}
		disk[0]++;
		drives>>=1;
	} 

}