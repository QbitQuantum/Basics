void KIconEditGrid::load( QImage *image)
{
  debug("KIconEditGrid::load");

  setUpdatesEnabled(false);

  if(image != 0L)
  {
    *img = *fixTransparence(image);
    //*img = image->convertDepth(32);
    //img->setAlphaBuffer(true);
  }
  else
  {
    QString msg = i18n("There was an error loading a blank image.\n");
    KMsgBox::message (this, i18n("Error"), msg.data());
    return;
  }

  setNumRows(img->height());
  setNumCols(img->width());

  for(int y = 0; y < numRows(); y++)
  {
    uint *l = (uint*)img->scanLine(y);
    for(int x = 0; x < numCols(); x++, l++)
    {
/*
      //uint gray = (qRgb(200, 200, 200) | OPAQUE_MASK);
      //uint bc = (TRANSPARENT | OPAQUE_MASK);
      //if(*l == gray || *l == bc || *l < 0xff000000)  // this is a hack but I couldn't save it as transparent otherwise
      if(*l < 0xff000000 || *l == (TRANSPARENT|OPAQUE_MASK))  // this is a hack but I couldn't save it as transparent otherwise
      {
        *l = TRANSPARENT;
      }
      //debug("KIcnGrid::load: %d %%", (((y*ncols)+x)/imgsize) * 100);
      //debug("KIconEditGrid::load: RGB: %d %d %d", qRed(*l), qGreen(*l), qBlue(*l));
*/
      setColor((y*numCols())+x, *l, false);
    }
    //debug("Row: %d", y);
    kapp->processEvents(200);
  }
  updateColors();
  emit sizechanged(numCols(), numRows());
  emit colorschanged(numColors(), data());
  emit changed(pixmap());
  setUpdatesEnabled(true);
  emit needPainting();
  //repaint(viewRect(), false);
}