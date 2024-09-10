void MtcOpcAdapter::gatherDeviceData()
{
 	static char name[] = "MtcOpcAdapter::gatherDeviceData";
	_set_se_translator( trans_func );  // correct thread?

	for(int i=0; i< _machines.size(); i++)
	{
		if(_machines[i]->IsConnected() )
		{
			try
			{
				// static	boost::mutex _alarm_mutex; - declare as static in shared class...
				//boost::mutex::scoped_lock  lock(_alarm_mutex);
				_machines[i]->_CriticalSection.Lock();
				_machines[i]->ExportValues();
				_machines[i]->_CriticalSection.Unlock();

			}
			catch(...)
			{
				GLogger << INFO << "MtcOpcAdapter::gatherDeviceData() exception "  << std::endl;
			}
		}
	}
}