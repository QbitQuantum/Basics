bool
ContainerWindow::FocusPreviousControl()
{
  Window *focused = GetFocusedWindow();
  Window *control = focused != NULL
    ? FindPreviousControl(focused)
    : NULL;
  if (control == NULL) {
    control = children.FindLastControl();
    if (control == NULL)
      return false;
  }

  control->SetFocus();
  return true;
}