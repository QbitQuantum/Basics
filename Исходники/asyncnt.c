void com_break(int on)
{
  COMMHANDLE h=ComGetHandle(hcModem);

  if (on)
    SetCommBreak(h);
  else ClearCommBreak(h);
}