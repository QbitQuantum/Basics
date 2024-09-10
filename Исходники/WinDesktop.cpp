WinDesktop::WinDesktop(ClipboardListener *extClipListener,
                       UpdateSendingListener *extUpdSendingListener,
                       AbnormDeskTermListener *extDeskTermListener)
: m_extClipListener(extClipListener),
  m_extUpdSendingListener(extUpdSendingListener),
  m_extDeskTermListener(extDeskTermListener),
  m_clToSrvChan(0),
  m_srvToClChan(0),
  m_clToSrvGate(0),
  m_srvToClGate(0),
  m_deskServWatcher(0),
  m_dispatcher(0),
  m_updateHandler(0),
  m_userInputClient(0),
  m_userInput(0),
  m_deskConf(0),
  m_gateKicker(0),
  m_wallPaper(0)
{
  Log::info(_T("Creating WinDesktop"));

  try {
    if (Configurator::getInstance()->getServiceFlag()) {
      m_deskServWatcher = new DesktopServerWatcher(this);

      m_clToSrvChan = new ReconnectingChannel(60000);
      m_srvToClChan = new ReconnectingChannel(60000);

      m_clToSrvGate = new BlockingGate(m_clToSrvChan);
      m_srvToClGate = new BlockingGate(m_srvToClChan);

      m_dispatcher = new DesktopSrvDispatcher(m_srvToClGate, this);

      m_updateHandler = new UpdateHandlerClient(m_clToSrvGate, m_dispatcher,
                                                this);

      UserInputClient *userInputClient =
        new UserInputClient(m_clToSrvGate, m_dispatcher, this);
      m_userInputClient = userInputClient;
      m_userInput = new SasUserInput(userInputClient);

      m_deskConf = new DesktopConfigClient(m_clToSrvGate);
      m_gateKicker = new GateKicker(m_clToSrvGate);
      m_dispatcher->resume();
      onConfigReload(0);
    } else {
      m_updateHandler = new LocalUpdateHandler(this);
      bool ctrlAltDelEnabled = false;
      m_userInput = new WindowsUserInput(this, ctrlAltDelEnabled);
      m_deskConf = new DesktopConfigLocal();
      applyNewConfiguration();
      m_wallPaper = new WallpaperUtil;
      m_wallPaper->updateWallpaper();
    }
    Configurator::getInstance()->addListener(this);
  } catch (Exception &ex) {
    Log::error(_T("exception during WinDesktop creaion: %s"), ex.getMessage());
    freeResource();
    throw;
  }
  resume();
}