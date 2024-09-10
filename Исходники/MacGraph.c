static void DrawToolBox (GRAPH_WINDOW *gw, INT tool)
{
  Rect r,dstRect;
  CGrafPtr myPort;
  PicHandle toolBox;
  WindowPtr theWindow;

  theWindow = MAC_WIN(gw);

  myPort = GetWindowPort(theWindow);
  SetPort(myPort);
  GetPortBounds(myPort,&r);

  toolBox = GetPicture(TOOLBOX_RSRC_ID);
  if (toolBox!=NULL)
  {
    SetRect(&dstRect,r.right-120,r.bottom-15,r.right-15,r.bottom);
    DrawPicture(toolBox,&dstRect);
  }

  SetRect(&dstRect,r.right-119+tool*15,r.bottom-14,r.right-104+tool*15,r.bottom);
  InvertRect(&dstRect);
}