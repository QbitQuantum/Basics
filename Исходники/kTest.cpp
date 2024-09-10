  void gameInit()
  {
    u32 w, h;
    kgmSystem::getDesktopDimension(w, h);

    game = new kGame();

    m_game = game;

    game->gInit();

    game->setRect(0, 0, w, h);

    kgmGameApp::Options* options = kgmGameApp::gameApplication()->options();

    if (options->map)
      game->gLoad(options->mapid);

    if (options->edit)
      game->gSwitch(kgmIGame::State_Edit);
  }