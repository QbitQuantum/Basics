void TrackPanel::FastScroll(int hoffset, int voffset)
{
#ifdef __WXMSW__
  REDRAW(this);
  return;
#endif

  int labelWidth = view->labelWidth;

  wxRect r;
  GetSize(&r.width, &r.height);
  r.width -= labelWidth;

  if (hoffset && voffset) {
    // Tricks don't work if we scroll horizontally AND vertically
    // at the same time
    REDRAW(this);
    return;
  }
  
  if (r.width != bitWidth || r.height != bitHeight || !bitmap) {
    // Don't try any tricks if we got resized, too
    REDRAW(this);
    return;
  }
  
  r.x = 0;
  r.y = 0;

  if (hoffset > 0)
    r.width = hoffset;
  else if (hoffset < 0) {
    r.x = (r.width + hoffset);
    r.width = -hoffset;
  }
  else if (voffset > 0)
    r.height = voffset;
  else if (voffset < 0) {
    r.y = (r.height + voffset);
    r.height = -voffset;
  }
  else
    return;

  r.x += labelWidth;
  r.y += 4;
  r.height -= 16;

  wxPaintDC dc(this);

  wxMemoryDC memDC;

  memDC.SelectObject(*bitmap);

  view->DrawTracks(&memDC, &r);

  ScrollWindow(hoffset, voffset);
  dc.Blit(r.x, r.y, r.width, r.height, &memDC, r.x, r.y, wxCOPY, FALSE);
    
}