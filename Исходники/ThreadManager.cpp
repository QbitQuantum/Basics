//Ожидание завершения выполнения задач из группы giW если 0 то ждем всех
void CThreadManager::Wait(GrupId giW,int nCount)
{
	CWait w;
	if(nCount==0)
	{
		//ищем
		boost::lock_guard<boost::mutex> l(m_cs);
		for(CTasks::iterator ti=m_arTask.begin();ti!=m_arTask.end();++ti)
			if(ti->second.m_Grup==giW)
				nCount+=ti->second.m_nCountCoin;

	}

	BeginTaskG(&w,0,giW,nCount,0);


    w.Wait();

}