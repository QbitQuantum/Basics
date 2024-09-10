void ZSplitter::move(CPoint point,CPoint dif)
{
  if(!(ownStyle&sp_StyleRight) ) dif.x = min(dif.x,0);
  if(!(ownStyle&sp_StyleLeft) )  dif.x = max(dif.x,0);
  if(!(ownStyle&sp_StyleBottom) )dif.y = max(dif.y,0);
  if(!(ownStyle&sp_StyleTop) )   dif.y = min(dif.y,0);

  CRect rc,parent;
  GetWindowRect(&rc);
  GetParent()->GetClientRect(&parent);
  GetParent()->ScreenToClient(&rc);
  int left = rc.left+dif.x;
  int top = rc.top+dif.y;
  bool canAll = true;  CRect rect;
  for(int i=0; i<(int)idxs.size();i++)
    if (!countRect(rect,i,dif))
      canAll = false;
  if(canAll && left>0 && left<parent.right && top>0 && top<parent.bottom )
  {
    for(int i=0; i<(int)idxs.size();i++)
    {
      countRect(rect,i,dif);
      CWnd *wnd = GetParent()->GetDlgItem(idxs[i]);
      wnd->MoveWindow(&rect);
      GetParent()->PostMessage(WM_MOVE_ZSPLITTER,0,(long)wnd->m_hWnd);
      wnd->UpdateWindow();
    }
    SetWindowPos(0,left,top,0,0,SWP_NOSIZE|SWP_NOZORDER);
    m_pointDragStart = point-dif;
  }
}