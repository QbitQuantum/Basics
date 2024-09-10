// static
void
IMEHandler::SetInputContext(nsWindow* aWindow, InputContext& aInputContext)
{
  // FYI: If there is no composition, this call will do nothing.
  NotifyIME(aWindow, REQUEST_TO_COMMIT_COMPOSITION);

  // Assume that SetInputContext() is called only when aWindow has focus.
  sPluginHasFocus = (aInputContext.mIMEState.mEnabled == IMEState::PLUGIN);

  bool enable = IsIMEEnabled(aInputContext);
  bool adjustOpenState = (enable &&
    aInputContext.mIMEState.mOpen != IMEState::DONT_CHANGE_OPEN_STATE);
  bool open = (adjustOpenState &&
    aInputContext.mIMEState.mOpen == IMEState::OPEN);

  aInputContext.mNativeIMEContext = nullptr;

#ifdef NS_ENABLE_TSF
  // Note that even while a plugin has focus, we need to notify TSF of that.
  if (sIsInTSFMode) {
    nsTextStore::SetInputContext(aInputContext);
    if (IsTSFAvailable()) {
      aInputContext.mNativeIMEContext = nsTextStore::GetTextStore();
    }
    // Currently, nsTextStore doesn't set focus to keyboard disabled document.
    // Therefore, we still need to perform the following legacy code.
  }
#endif // #ifdef NS_ENABLE_TSF

  nsIMEContext IMEContext(aWindow->GetWindowHandle());
  if (enable) {
    IMEContext.AssociateDefaultContext();
    if (!aInputContext.mNativeIMEContext) {
      aInputContext.mNativeIMEContext = static_cast<void*>(IMEContext.get());
    }
  } else if (!aWindow->Destroyed()) {
    // Don't disassociate the context after the window is destroyed.
    IMEContext.Disassociate();
    if (!aInputContext.mNativeIMEContext) {
      // The old InputContext must store the default IMC.
      aInputContext.mNativeIMEContext =
        aWindow->GetInputContext().mNativeIMEContext;
    }
  }

  if (adjustOpenState) {
#ifdef NS_ENABLE_TSF
    if (IsTSFAvailable()) {
      nsTextStore::SetIMEOpenState(open);
      return;
    }
#endif // #ifdef NS_ENABLE_TSF
    IMEContext.SetOpenState(open);
  }
}