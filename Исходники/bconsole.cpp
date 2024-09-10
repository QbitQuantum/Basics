TWindow *__FASTCALL__ PleaseWaitWnd()
{
   TWindow *w;
   w = CrtDlgWndnls(SYSTEM_BUSY,14,1);
   w->goto_xy(1,1); w->puts(PLEASE_WAIT);
   return w;
}