//
/// Paints the DIB onto the window.
//
void
TPictureWindow::Paint(TDC& dc, bool /*erase*/, TRect& /*rect*/)
{
  TPointer<TPalette> palette(0);
  bool hasPalette = ToBool(dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE);

  TDib* dib = GetDib();
  if (dib) {
    if (hasPalette) {
      palette = new TPalette(*GetDib());
      dc.SelectObject(*palette);
      dc.RealizePalette();
    }

    // figure out upper left corner of the client area
    //
    TRect clientRect(GetClientRect());
    TPoint sourcePoint(0, 0);

    // adjust the upper left corner for centering picture
    //
    if (HowToDisplay == Center) {
      // determine offsets
      //
      int offsetX = abs(dib->Width() - clientRect.Width()) / 2;
      if (dib->Width() > clientRect.Width())
        sourcePoint.x += offsetX;
      else
        clientRect.Offset(offsetX, 0);

      int offsetY = abs(dib->Height() - clientRect.Height()) / 2;
      if (dib->Height() > clientRect.Height())
        sourcePoint.y += offsetY;
      else
        clientRect.Offset(0, offsetY);
    }

    // adjust the lower right corner
    //
    if (HowToDisplay != Stretch) {
      clientRect.bottom = clientRect.top + dib->Height();
      clientRect.right  = clientRect.left + dib->Width();

      // if the picture is larger than screen dimensions,
      // adjust the upper left corner.
      //
      clientRect.top   -= sourcePoint.y;
      clientRect.left  -= sourcePoint.x;
    }

    // display the dib
    //
    switch (HowToDisplay) {
      case UpperLeft:
      case Center:
        dc.SetDIBitsToDevice(clientRect, sourcePoint, *dib);
//        if(!dc.SetDIBitsToDevice(clientRect, sourcePoint, *dib)){
//          TSystemMessage().MessageBox();
//        }
        break;
      case Stretch: {
        TRect sourceRect(0, 0, dib->Width(), dib->Height());
        dc.StretchDIBits(clientRect, sourceRect, *dib);
        break;
      }
    } // switch HowToDisplay

    dc.RestoreObjects();
  }
}