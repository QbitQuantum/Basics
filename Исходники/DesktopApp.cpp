void DesktopApp::Run()
{
	// ------------- init Engine objects
	Assert(!Engine::instance().isInit());
	Engine::instance().initLowLevel();

	try
	{
		// ------------- call main class init()
		m_mainClass->init();
		m_frameDurationCounter.init();

		while (Engine::instance().isRunning() && !reinterpret_cast<const DesktopWindow*>(getWindow())->mustBeDestroyed()) // ------------ MAIN LOOP
		{
			// ------------ manage events

			this->manageEvents();

			if (!m_suspended)
			{
				// ------------- call main class update()

				bool needProcessAgain = m_mainClass->update();

				if (reinterpret_cast<const DesktopWindow*>(getWindow())->mustBeDestroyed() || !Engine::instance().isRunning()) break;

				Engine::instance().updateInternals();

				// ------------ call main class render()

				this->BeginDraw();
				m_mainClass->render();
				this->EndDraw();
			}

			Engine::instance().m_frameDuration = m_frameDurationCounter.retrieve();
		}

		m_mainClass->deinit();
		Engine::instance().deinitLowLevel();
	}
	catch (EngineError e)
	{
		outputln("Caught EngineError");
		if (this->isDrawing()) this->EndDraw();
		m_isCrashedState = true;

		while (true)
		{
			this->manageEvents();
			Engine::instance().updateInternals();

			this->BeginDraw();
			Engine::instance().clearScreen(CoreUtils::colorBlack);
			Engine::instance().getScene2DMgr().drawText(NULL, Utils::convertWStringToString(e.getFullText(), false).c_str(), Int2(20, 40), 18, CoreUtils::colorWhite);
			this->EndDraw();
			Engine::instance().m_frameDuration = m_frameDurationCounter.retrieve();
		}
	}

	cleanup();

	uninitializeWindow();

	outputln("======== CLEANUP DONE ========");

#ifndef NDEBUG
	// http://gamedev.stackexchange.com/questions/14633/what-do-these-state-creation-warnings-mean-in-the-dx11-debug-output
	typedef HRESULT(__stdcall *fPtr)(const IID&, void**);
	HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
	fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");
	IDXGIDebug* pDxgiDebug;
	DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDxgiDebug);
	pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
#endif
}