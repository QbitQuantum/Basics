	//
	// 函数：bool onMessage(UINT message, WPARAM wParam, LPARAM lParam)
	//
	// 目的：窗口消息处理函数
	//
	// 返回值：已处理，返回true，否则返回false
	//
	bool onMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		// 如果是键盘消息，获取键盘状态
		if (message == WM_KEYDOWN || message == WM_KEYUP)
		{
			if (!getKeyboardState())
			{
				return false;
			}
		}
		
		// 获取鼠标状态
		getMouseState(message);

		bool handled = false;

		MSG_LISTENER_MAP::iterator at = myListenerMap.find(message);
		if (at != myListenerMap.end())
		{
			LISTENER_LIST& listeners = at->second;
			for (LISTENER_LIST::iterator it = listeners.begin(); 
				 it != listeners.end() && !handled; ++it)
			{
				YCIInputListener* listener = *it;
				if (listener->onMessage(message, wParam, lParam))
				{
					handled = true;
				}
			}
		}
		return handled;
	}