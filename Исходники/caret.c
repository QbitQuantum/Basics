BOOL
APIENTRY
NtUserCreateCaret(
   HWND hWnd,
   HBITMAP hBitmap,
   int nWidth,
   int nHeight)
{
   PWND Window;
   PTHREADINFO pti;
   PUSER_MESSAGE_QUEUE ThreadQueue;
   DECLARE_RETURN(BOOL);

   TRACE("Enter NtUserCreateCaret\n");
   UserEnterExclusive();

   if(!(Window = UserGetWindowObject(hWnd)))
   {
      RETURN(FALSE);
   }

   if(Window->head.pti->pEThread != PsGetCurrentThread())
   {
      EngSetLastError(ERROR_ACCESS_DENIED);
      RETURN(FALSE);
   }

   pti = PsGetCurrentThreadWin32Thread();
   ThreadQueue = pti->MessageQueue;

   if (ThreadQueue->CaretInfo->Visible)
   {
      IntKillTimer(Window, IDCARETTIMER, TRUE);
      co_IntHideCaret(ThreadQueue->CaretInfo);
   }

   ThreadQueue->CaretInfo->hWnd = hWnd;
   if(hBitmap)
   {
      ThreadQueue->CaretInfo->Bitmap = hBitmap;
      ThreadQueue->CaretInfo->Size.cx = ThreadQueue->CaretInfo->Size.cy = 0;
   }
   else
   {
      if (nWidth == 0)
      {
          nWidth = UserGetSystemMetrics(SM_CXBORDER);
      }
      if (nHeight == 0)
      {
          nHeight = UserGetSystemMetrics(SM_CYBORDER);
      }
      ThreadQueue->CaretInfo->Bitmap = (HBITMAP)0;
      ThreadQueue->CaretInfo->Size.cx = nWidth;
      ThreadQueue->CaretInfo->Size.cy = nHeight;
   }
   ThreadQueue->CaretInfo->Visible = 0;
   ThreadQueue->CaretInfo->Showing = 0;

   IntSetTimer( Window, IDCARETTIMER, gpsi->dtCaretBlink, CaretSystemTimerProc, TMRF_SYSTEM );

   IntNotifyWinEvent(EVENT_OBJECT_CREATE, Window, OBJID_CARET, CHILDID_SELF, 0);

   RETURN(TRUE);

CLEANUP:
   TRACE("Leave NtUserCreateCaret, ret=%i\n",_ret_);
   UserLeave();
   END_CLEANUP;
}