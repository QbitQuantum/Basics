/*static*/ LRESULT CALLBACK 
sbWindowMoveService::CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
  // This is a message we shouldn't process. See SetWindowHookEx docs
  // on MSDN for more information about how to process window hook
  // messages.
  if(nCode < 0) {
    return CallNextHookEx(NULL, nCode, wParam, lParam);
  }

  PCWPSTRUCT msg = reinterpret_cast<PCWPSTRUCT>(lParam);
  
  sbWindowMoveService *self = 
    reinterpret_cast<sbWindowMoveService *>(::GetPropW(msg->hwnd, PROP_WMS_INST));
  if (!self) {
    // This wasn't a window that we're interested in, don't do anything
    return CallNextHookEx(NULL, nCode, wParam, lParam);
  }

  if(msg->message == WM_WINDOWPOSCHANGING) {
    // if the window didn't actually move, then we don't actually care
    WINDOWINFO wi;
    wi.cbSize = sizeof(WINDOWINFO);
    if (GetWindowInfo(msg->hwnd, &wi)) {
      RECT* oldpos = &wi.rcWindow;
      WINDOWPOS* newpos = (WINDOWPOS*)msg->lParam;
      if (newpos->flags & SWP_NOMOVE) {
        return CallNextHookEx(NULL, nCode, wParam, lParam);
      }
    }

    sbWindowMoveService::resizing_t::iterator it = 
     self->mResizing.find(msg->hwnd);

    if(it == self->mResizing.end()) {
      self->mResizing.insert(std::make_pair<HWND, bool>(msg->hwnd, true));
      CallListenerMoveStarted(msg->hwnd, self->mListeners);
    }
    else if(!it->second) {
      it->second = true;
      CallListenerMoveStarted(msg->hwnd, self->mListeners);
    }
  }
  else if(msg->message == WM_WINDOWPOSCHANGED) {
    sbWindowMoveService::resizing_t::iterator it = 
      self->mResizing.find(msg->hwnd);

    if(it != self->mResizing.end() &&
       it->second == true) {
      
      nsCOMPtr<nsITimer> timer;
      timers_t::iterator itTimer = self->mTimers.find(msg->hwnd);
      if(itTimer == self->mTimers.end()) {
        nsresult rv = NS_ERROR_UNEXPECTED;
        
        timer = do_CreateInstance("@mozilla.org/timer;1");
        self->mTimers.insert(
          std::make_pair<HWND, nsCOMPtr<nsITimer> >(msg->hwnd, timer));
      }
      else {
        timer = itTimer->second;
      }

      if(timer) {
        self->mTimersToWnd.insert(
          std::make_pair<nsITimer*, HWND>(timer.get(), msg->hwnd));
        timer->InitWithCallback(self, 1000, nsITimer::TYPE_ONE_SHOT);
      }
    }
  }

  return CallNextHookEx(NULL, nCode, wParam, lParam);
}