	void Multitouch::removeEventListener(MultitouchEventListener*listener)
	{
		if(listener == nullptr)
		{
			throw IllegalArgumentException("listener", "null");
		}
		
		if(Multitouch_callingListeners)
		{
			Multitouch_changedListeners_mutex.lock();
			Multitouch_changedListeners.add(Pair<MultitouchEventListener*,bool>(listener,false));
			Multitouch_changedListeners_mutex.unlock();
		}
		Multitouch_eventListeners_mutex.lock();
		unsigned int index = Multitouch_eventListeners.indexOf(listener);
		while(index != ARRAYLIST_NOTFOUND)
		{
			Multitouch_eventListeners.remove(index);
			index = Multitouch_eventListeners.indexOf(listener);
		}
		Multitouch_eventListeners_mutex.unlock();
	}