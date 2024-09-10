bool
nsXBLKeyEventHandler::ExecuteMatchedHandlers(
                        nsIDOMKeyEvent* aKeyEvent,
                        uint32_t aCharCode,
                        const IgnoreModifierState& aIgnoreModifierState)
{
  WidgetEvent* event = aKeyEvent->GetInternalNSEvent();
  nsCOMPtr<EventTarget> target = aKeyEvent->InternalDOMEvent()->GetCurrentTarget();

  bool executed = false;
  for (uint32_t i = 0; i < mProtoHandlers.Length(); ++i) {
    nsXBLPrototypeHandler* handler = mProtoHandlers[i];
    bool hasAllowUntrustedAttr = handler->HasAllowUntrustedAttr();
    if ((event->mFlags.mIsTrusted ||
        (hasAllowUntrustedAttr && handler->AllowUntrustedEvents()) ||
        (!hasAllowUntrustedAttr && !mIsBoundToChrome && !mUsingContentXBLScope)) &&
        handler->KeyEventMatched(aKeyEvent, aCharCode, aIgnoreModifierState)) {
      handler->ExecuteHandler(target, aKeyEvent);
      executed = true;
    }
  }
#ifdef XP_WIN
  // Windows native applications ignore Windows-Logo key state when checking
  // shortcut keys even if the key is pressed.  Therefore, if there is no
  // shortcut key which exactly matches current modifier state, we should
  // retry to look for a shortcut key without the Windows-Logo key press.
  if (!executed && !aIgnoreModifierState.mOS) {
    WidgetKeyboardEvent* keyEvent = event->AsKeyboardEvent();
    if (keyEvent && keyEvent->IsOS()) {
      IgnoreModifierState ignoreModifierState(aIgnoreModifierState);
      ignoreModifierState.mOS = true;
      return ExecuteMatchedHandlers(aKeyEvent, aCharCode, ignoreModifierState);
    }
  }
#endif
  return executed;
}