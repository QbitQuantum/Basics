static int winValCtlColor(Ihandle* ih, HDC hdc, LRESULT *result)
{
  COLORREF cr;
  if (iupwinGetParentBgColor(ih, &cr))
  {
    SetDCBrushColor(hdc, cr);
    *result = (LRESULT)GetStockObject(DC_BRUSH);
    return 1;
  }
  return 0;
}