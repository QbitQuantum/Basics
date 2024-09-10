	//----------------------------------------------------------------------------
	void WorldViewWindowManager::setActiveWindowIndex(size_t _index)
	{
		WorldViewWindow* window = getWindow(_index);
		setActiveWindow(window);
	}