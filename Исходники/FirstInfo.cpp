void CFirstInfo::OnLButtonDown(UINT nFlags, CPoint point) 
{
  int id=0;
  CWnd* w=ChildWindowFromPoint(point);
  if (w)
    id=w->GetDlgCtrlID();

  // Select
  switch(id) {
    case 0: break;
    case IDC_SPLASH:
      this->ClientToScreen(&point);
      w->ScreenToClient(&point);
    if ((point.y>=100) && (point.y<=110) || (point.y<=80)) {
      if (!ShellExecute(NULL,"open","http://www.httrack.com","","",SW_RESTORE)) {
      }
    }
    break;
  }

  CDialog::OnLButtonDown(nFlags, point);
}