// copy to clipboard aka X11 selection
void KfindWindow::copySelection()
{
  TQDragObject *drag_obj = dragObject();

  if (drag_obj)
  {
    TQClipboard *cb = kapp->clipboard();
    cb->setData(drag_obj);
  }
}