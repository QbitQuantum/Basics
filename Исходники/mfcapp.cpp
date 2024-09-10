static void
mfc_show()
{
  if (!(mfc_showing&1)) {
    CMDIFrameWnd *fw = (CMDIFrameWnd *)(the_boss.m_pMainWnd);
    fw->ShowWindow(the_boss.m_nCmdShow);
    fw->UpdateWindow();
    mfc_showing |= 1;
  }
}