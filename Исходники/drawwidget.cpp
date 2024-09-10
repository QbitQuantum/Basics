void DrawWidget::drawToScreen()
{
#ifndef SINGLE_DRAWING_BUFFER
  bitBlt(this, 0, 0, _buffer, 0, 0, width(), height());
#endif
}