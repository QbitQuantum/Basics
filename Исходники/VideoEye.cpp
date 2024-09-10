void CVideoEyeApp::LoadLaguage()
{
	//配置文件路径
	char conf_path[300]={0};
	//获得exe绝对路径
	GetModuleFileNameA(NULL,(LPSTR)conf_path,300);//
	//获得exe文家夹路径
	strrchr( conf_path, '\\')[0]= '\0';//
	strcat(conf_path,"\\configure.ini");
	//存储属性的字符串
	char conf_val[300]={0};

	if((_access(conf_path, 0 )) == -1 ){  
		//配置文件不存在，直接返回
	}else{
		GetPrivateProfileStringA("Settings","language",NULL,conf_val,300,conf_path);
		if(strcmp(conf_val,"Chinese")==0){
			SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_DEFAULT));
		}else if(strcmp(conf_val,"English")==0){
			SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT));
		}
		
	}
	return;
}