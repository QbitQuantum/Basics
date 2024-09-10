  kgmIGame* android_init_game()
  {
    u32 w, h;
    kgmSystem::getDesktopDimension(w, h);
    m_game = game = new kGame();
    game->setRect(0, 0, w, h);

    return game;
  }