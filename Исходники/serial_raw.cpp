void serial_raw::set_break(int mode)
{
  BX_DEBUG (("set break %s", mode?"on":"off"));
#ifdef WIN32
  if (mode) {
    SetCommBreak(hCOM);
  } else {
    ClearCommBreak(hCOM);
  }
#endif
}