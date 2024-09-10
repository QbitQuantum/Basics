static int winMenuSetBgColorAttrib(Ihandle* ih, const char* value)
{
  unsigned char r, g, b;
  /* must use IupGetAttribute to use inheritance */
  if (iupStrToRGB(value, &r, &g, &b))
  {
    MENUINFO menuinfo;
    menuinfo.cbSize = sizeof(MENUINFO);
    menuinfo.fMask = MIM_BACKGROUND;
    menuinfo.hbrBack = iupwinBrushGet(RGB(r,g,b)); 
    SetMenuInfo((HMENU)ih->handle, &menuinfo);
    winMenuUpdateBar(ih);
  }
  return 1;
}