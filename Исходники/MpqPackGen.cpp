void CMpqPackGen::GetConfigInfo()
{
	m_iPackTotal = ::GetPrivateProfileInt("PackInfo","PackTotal",0,"./PackageGenConfig.ini");
	for ( int i=1;i<=m_iPackTotal;i++ )
	{
		char Ext[10] =  {0};
		char Name[10] = {0};
		char Path[10] = {0};
		char Temp[500] = {0};

		_MPQPackInfo	 info;

		sprintf(Name,"Name%d",i);
		sprintf(Path,"Path%d",i);
		sprintf(Ext,"Ext%d",i);

		::GetPrivateProfileString("PackInfo",Name,NULL,Temp,500,"./PackageGenConfig.ini");
		_mbslwr((byte*)Temp);
		info.strPackName = Temp;

		::GetPrivateProfileString("PackInfo",Path,NULL,Temp,500,"./PackageGenConfig.ini");
		_mbslwr((byte*)Temp);
		string path = Temp;
		string::size_type tmpPos;
		while ( ( tmpPos = path.find(" ") )!= string::npos )
		{
			path.erase(tmpPos, 1);
		}
		
		replace(path.begin(),path.end(),'\\','/');

		string::size_type pos = path.find("&");
		while ( pos != string::npos )				//对应多个路径
		{
			string PathPart = path.substr(0,pos);
			info.vecPackPath.push_back(PathPart);
			path = path.substr(pos+1);
			pos = path.find("&");
		}
		info.vecPackPath.push_back(path);

		::GetPrivateProfileString("PackInfo",Ext,NULL,Temp,500,"./PackageGenConfig.ini");
		_mbslwr((byte*)Temp);
		string ext = Temp ;

		while ( ( tmpPos = ext.find(" ") )!= string::npos )
		{
			ext.erase(tmpPos, 1);
		}

		pos = ext.find("&");
		while ( pos != string::npos )				//对应多个扩展名
		{
			string ExtPart = ext.substr(0,pos);
			info.vecExt.push_back(ExtPart);
			ext = ext.substr(pos+1);
			pos = ext.find("&");
		}
		info.vecExt.push_back(ext);
	
		m_vecPackInfo.push_back(info);
		
	}//for end

   
	int CompressType = ::GetPrivateProfileInt("CompressType",".wav",0,"./PackageGenConfig.ini");
	m_mapCompressType.insert( map<string,int>::value_type(".wav ",CompressType) );

	CompressType = ::GetPrivateProfileInt("CompressType",".zip",0,"./PackageGenConfig.ini");
	m_mapCompressType.insert( map<string,int>::value_type(".zip",CompressType) );

	CompressType = ::GetPrivateProfileInt("CompressType",".rar",0,"./PackageGenConfig.ini");
	m_mapCompressType.insert( map<string,int>::value_type(".rar",CompressType) );

	CompressType = ::GetPrivateProfileInt("CompressType",".mpq",0,"./PackageGenConfig.ini");
	m_mapCompressType.insert( map<string,int>::value_type(".mpq",CompressType) );

	CompressType = ::GetPrivateProfileInt("CompressType","*.*",0,"./PackageGenConfig.ini");
	m_mapCompressType.insert( map<string,int>::value_type("*.*",CompressType) );

	m_bTestVersion = ::GetPrivateProfileInt("VersionType","Version",0,"./PackageGenConfig.ini");

}//GetConfigInfo end