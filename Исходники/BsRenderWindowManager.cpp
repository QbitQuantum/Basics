	SPtr<RenderWindow> RenderWindowManager::create(RENDER_WINDOW_DESC& desc, SPtr<RenderWindow> parentWindow)
	{
		UINT32 id = ct::RenderWindowManager::instance().mNextWindowId.fetch_add(1, std::memory_order_relaxed);

		SPtr<RenderWindow> renderWindow = createImpl(desc, id, parentWindow);
		renderWindow->_setThisPtr(renderWindow);
		
		{
			Lock lock(mWindowMutex);

			mWindows[renderWindow->mWindowId] = renderWindow.get();
		}

		if (renderWindow->getProperties().isModal)
			mModalWindowStack.push_back(renderWindow.get());

		renderWindow->initialize();
		
		return renderWindow;
	}