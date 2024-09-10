HotkeyCombo::~HotkeyCombo()
{
  if (ID)
  {
    GlobalDeleteAtom(ID);
  }
}