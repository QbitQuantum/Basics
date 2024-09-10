bool SApplication::SearchOldProcess(int &pid,int &ppid,SString &name)
{
	//进程是否存在
	SStringList plist;//pid,ppid,name;....
	SString sLine;
	int p,i,cnt = SApi::GetSystemProcess(plist);
	for(i=0;i<cnt;i++)
	{
		sLine = *plist[i];
		//LOGDEBUG("MOUDLE:%s",sLine.data());
		pid = SString::GetIdAttributeI(1,sLine,",");
		ppid= SString::GetIdAttributeI(2,sLine,",");
		name= SString::GetIdAttribute( 3,sLine,",");
#ifdef WIN32
		name += ".exe";
#endif

		if(pid == SApi::GetPid())
			continue;//忽略自身的进程
		p = name.find(m_sModule);
		if(p < 0)
			continue;
		if(name.length() == p+m_sModule.length() ||
			 name.at(p+m_sModule.length()) == ' ')
		{
			LOGDEBUG("得到当前进程对应的进程!");
			return true;
		}
	}
	return false;
}