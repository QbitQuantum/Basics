bool DesktopSelector::selectDesktop(const StringStorage *name)
{
  HDESK desktop;
  if (name) {
    desktop = getDesktop(name);
  } else {
    desktop = getInputDesktop();
  }

  bool result = setDesktopToCurrentThread(desktop) != 0;
  closeDesktop(desktop);

  return result;
}