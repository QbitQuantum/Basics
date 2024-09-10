void X11Wnd::onMouseMove(void)
{
  // Make sure input events are redirected to this window
  setActiveWindow(this);
}