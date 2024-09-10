void XWindow::ControlFocusPrevious()
{
    Collection<Control *> focusables = ControlsEnumFocusable();
    if (focusables.Count() == 0) return;

    Control *focused = ControlGetFocused();
    if (focused != NULL) focused->SetFocus(false);
    int ix = focused == NULL ? 0 : controls->FindFirstIx(focused);
    if (ix == -1) return;

    ix += controls->Count() - 1;
    ix = ix % controls->Count();
    (*controls)[ix]->SetFocus(true);
}