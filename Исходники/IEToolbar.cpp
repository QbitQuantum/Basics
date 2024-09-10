bool IEToolbar::onToolbarKillFocus(const NMTOOLBAR& messageInfo,
                                   LRESULT& lResult) {
  UNREFERENCED_PARAMETER(messageInfo);
  UNREFERENCED_PARAMETER(lResult);

  const IUnknownPtr control = getControlUnknown();
  const HRESULT chageFocusResult = site_->OnFocusChangeIS(control, FALSE);
  if (FAILED(chageFocusResult)) {
    _com_raise_error(chageFocusResult);
  }

  return true;
}