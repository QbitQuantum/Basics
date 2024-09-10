static int winCanvasSetDYAttrib(Ihandle *ih, const char *value)
{
  if (ih->data->sb & IUP_SB_VERT)
  {
    double posy, ymin, ymax;
    float dy;
    int iposy, ipagey;

    if (!iupStrToFloat(value, &dy))
      return 1;

    ymin = iupAttribGetFloat(ih, "YMIN");
    ymax = iupAttribGetFloat(ih, "YMAX");
    posy = ih->data->posy;

    iupCanvasCalcScrollIntPos(ymin, ymax, dy, posy, 
                              IUP_SB_MIN, IUP_SB_MAX, &ipagey, &iposy);

    if (dy >= (ymax-ymin))
    {
      if (iupAttribGetBoolean(ih, "YAUTOHIDE"))
        ShowScrollBar(ih->handle, SB_VERT, FALSE);
      else
        EnableScrollBar(ih->handle, SB_VERT, ESB_DISABLE_BOTH);
      return 1;
    }
    else
    {
      ShowScrollBar(ih->handle, SB_VERT, TRUE);
      EnableScrollBar(ih->handle, SB_VERT, ESB_ENABLE_BOTH);
    }

    winCanvasSetScrollInfo(ih->handle, IUP_SB_MIN, IUP_SB_MAX, iposy, ipagey, SB_VERT);

    /* update position because it could be corrected */
    iupCanvasCalcScrollRealPos(ymin, ymax, &posy, 
                               IUP_SB_MIN, IUP_SB_MAX, ipagey, &iposy);

    ih->data->posy = (float)posy;
  }
  return 1;
}