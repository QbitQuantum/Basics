bool
nsXBLPrototypeHandler::ModifiersMatchMask(nsIDOMUIEvent* aEvent,
                                          bool aIgnoreShiftKey)
{
  WidgetInputEvent* inputEvent = aEvent->GetInternalNSEvent()->AsInputEvent();
  NS_ENSURE_TRUE(inputEvent, false);

  if (mKeyMask & cMetaMask) {
    if (inputEvent->IsMeta() != ((mKeyMask & cMeta) != 0)) {
      return false;
    }
  }

  if (mKeyMask & cOSMask) {
    if (inputEvent->IsOS() != ((mKeyMask & cOS) != 0)) {
      return false;
    }
  }

  if (mKeyMask & cShiftMask && !aIgnoreShiftKey) {
    if (inputEvent->IsShift() != ((mKeyMask & cShift) != 0)) {
      return false;
    }
  }

  if (mKeyMask & cAltMask) {
    if (inputEvent->IsAlt() != ((mKeyMask & cAlt) != 0)) {
      return false;
    }
  }

  if (mKeyMask & cControlMask) {
    if (inputEvent->IsControl() != ((mKeyMask & cControl) != 0)) {
      return false;
    }
  }

  return true;
}