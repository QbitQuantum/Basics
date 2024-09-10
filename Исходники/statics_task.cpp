CStaticsTask * CStaticsTask::getStaticsTask(uint32_t sourceId)
{
	std::map<uint32_t,CStaticsTask *>::iterator it=gMapCStaticsTask.find(sourceId); 
	if( it!=gMapCStaticsTask.end())
	{
		return (*it).second;
	}
	instanceLock.lock();
	it=gMapCStaticsTask.find(sourceId);
	if(it==gMapCStaticsTask.end())
	{
		CStaticsTask * p = new CStaticsTask(sourceId);
		gMapCStaticsTask.insert(std::pair<uint32_t,CStaticsTask *>(sourceId,p));
        //每个dataid(view)建了一个线程池
		if(gMapCStaticsTask.size()==1) CStaticsTask::gThreadTaskPool  = new Common::CThreadPool(16,20,100000);
		instanceLock.unlock();
		return p;
	}
	else
	{
		instanceLock.unlock();
		return (*it).second;
	}
}