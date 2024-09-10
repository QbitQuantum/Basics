void HooksUpdateDetector::execute()
{
  m_log->info(_T("Hooks update detector thread id = %d"), getThreadId());

  if (!isTerminating() && m_targetWin != 0) {
    m_targetWin->createWindow();
    m_log->info(_T("Hooks target window has been created (hwnd = %d)"),
              m_targetWin->getHWND());
  }

  try {
    UipiControl uipiControl(m_log);
    uipiControl.allowMessage(HookDefinitions::SPEC_IPC_CODE,
                             m_targetWin->getHWND());
  } catch (Exception &e) {
    terminate();
    m_log->error(e.getMessage());
  }

  bool hookInstalled = false;
  while (!isTerminating() && !hookInstalled) {
    try {
      m_hookInstaller->install(m_targetWin->getHWND());
      hookInstalled = true;
    } catch (Exception &e) {
      m_log->error(_T("Hooks installing failed, wait for the next trying: %s"),
                 e.getMessage());
      m_initWaiter.waitForEvent(5000);
      try {
        m_hookInstaller->uninstall();
      } catch (Exception &e) {
        m_log->error(_T("Hooks uninstalling failed: %s"),
                   e.getMessage());
      }
    }
  }

  start32Loader();

  if (!isTerminating()) {
    m_log->info(_T("Hooks update detector has been successfully initialized"));
  }

  MSG msg;
  while (!isTerminating()) {
    if (PeekMessage(&msg, m_targetWin->getHWND(), 0, 0, PM_REMOVE) != 0) {
      if (msg.message == HookDefinitions::SPEC_IPC_CODE) {
        Rect rect((INT16)(msg.wParam >> 16), (INT16)(msg.wParam & 0xffff),
                  (INT16)(msg.lParam >> 16), (INT16)(msg.lParam & 0xffff));
        if (!rect.isEmpty()) {
          m_updateKeeper->addChangedRect(&rect);
          m_updateTimer.sear();
        }
      } else {
        DispatchMessage(&msg);
      }
    } else {