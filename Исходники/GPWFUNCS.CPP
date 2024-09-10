CCustomToolTipCtrl::CCustomToolTipCtrl(CWnd* pParentWnd)
  {
  ASSERT(pParentWnd);
  pParentWnd->EnableToolTips(TRUE);
  VERIFY(Create(pParentWnd));
  CWnd* w = pParentWnd->GetWindow(GW_CHILD);
  while (w)
    {
    AddTool(w);
    w = w->GetWindow(GW_HWNDNEXT);
    }
  if (GetToolCount()>0)
    Activate(TRUE);
  }