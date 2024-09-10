void SDLEventSystem::executeEventSystem(RLMachine& machine) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN: {
        if (raw_handler_)
          raw_handler_->pushInput(event);
        else
          handleKeyDown(machine, event);
        break;
      }
      case SDL_KEYUP: {
        if (raw_handler_)
          raw_handler_->pushInput(event);
        else
          handleKeyUp(machine, event);
        break;
      }
      case SDL_MOUSEMOTION: {
        if (raw_handler_)
          raw_handler_->pushInput(event);
        handleMouseMotion(machine, event);
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP: {
        if (raw_handler_)
          raw_handler_->pushInput(event);
        else {
          LOGD("got mouse event\n");
          handleMouseButtonEvent(machine, event);
        }
        break;
      }
      case SDL_QUIT:
        machine.halt();
        break;
      case SDL_ACTIVEEVENT:
        if (raw_handler_)
          raw_handler_->pushInput(event);
        handleActiveEvent(machine, event);
        break;
      case SDL_VIDEOEXPOSE: {
        machine.system().graphics().forceRefresh();
        break;
      }
    }
  }
}