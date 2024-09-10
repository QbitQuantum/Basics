void KeyboardEvent::GetInitDict(KeyboardEventInit& aParam)
{
  GetKey(aParam.mKey);
  GetCode(aParam.mCode);
  aParam.mLocation = Location();
  aParam.mRepeat = Repeat();
  aParam.mIsComposing = IsComposing();

  // legacy attributes
  aParam.mKeyCode = KeyCode();
  aParam.mCharCode = CharCode();
  aParam.mWhich = Which();

  // modifiers from EventModifierInit
  aParam.mCtrlKey = CtrlKey();
  aParam.mShiftKey = ShiftKey();
  aParam.mAltKey = AltKey();
  aParam.mMetaKey = MetaKey();

  WidgetKeyboardEvent* internalEvent = mEvent->AsKeyboardEvent();
  aParam.mModifierAltGraph = internalEvent->IsAltGraph();
  aParam.mModifierCapsLock = internalEvent->IsCapsLocked();
  aParam.mModifierFn = internalEvent->IsFn();
  aParam.mModifierFnLock = internalEvent->IsFnLocked();
  aParam.mModifierNumLock = internalEvent->IsNumLocked();
  aParam.mModifierOS = internalEvent->IsOS();
  aParam.mModifierScrollLock = internalEvent->IsScrollLocked();
  aParam.mModifierSymbol = internalEvent->IsSymbol();
  aParam.mModifierSymbolLock = internalEvent->IsSymbolLocked();

  // EventInit
  aParam.mBubbles =  internalEvent->mFlags.mBubbles;
  aParam.mCancelable = internalEvent->mFlags.mCancelable;
}