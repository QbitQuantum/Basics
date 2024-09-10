void ScalePlot::paintEvent (QPaintEvent *)
{
  bitBlt(this, 0, 0, &buffer);
}