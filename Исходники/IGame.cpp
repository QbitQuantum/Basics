  void IGame::destroy() {
    if(_state != GameState::DESTROYED) {
      _state = GameState::DESTROYED;

      SDL_StopTextInput();
      if(_screenManager) {
        delete _screenManager;
      }
      onExit();
    }
  }