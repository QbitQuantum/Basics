  int AppBase::run()
  {
    if (!onInit()) {
      return -1;
    }

    frame_timer.reset();
    // game main loop begin .
    SDL_Event evnt;
    leave_main_loop = false;
    while (!leave_main_loop) {
      if (SDL_PollEvent(&evnt)) {
        processGlobalEvent(evnt);
        if (onEvent(evnt) == false) {
          processUnhandleEvent(evnt);
        }
      }

      if (!leave_main_loop) {
        onUpdate();
        onRender();
      }

      frame_timer.update();
    }

    onExit();
    return 0;
  }