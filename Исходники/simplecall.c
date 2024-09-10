/*
 * @implemented
 */
DWORD_PTR
APIENTRY
NtUserCallTwoParam(
   DWORD_PTR Param1,
   DWORD_PTR Param2,
   DWORD Routine)
{
   PWND Window;
   DECLARE_RETURN(DWORD_PTR);

   TRACE("Enter NtUserCallTwoParam\n");
   UserEnterExclusive();

   switch(Routine)
   {
      case TWOPARAM_ROUTINE_SETMENUBARHEIGHT:
         {
            DWORD_PTR Ret;
            PMENU_OBJECT MenuObject = IntGetMenuObject((HMENU)Param1);
            if(!MenuObject)
               RETURN( 0);

            if(Param2 > 0)
            {
               Ret = (MenuObject->MenuInfo.Height == (int)Param2);
               MenuObject->MenuInfo.Height = (int)Param2;
            }
            else
               Ret = (DWORD_PTR)MenuObject->MenuInfo.Height;
            IntReleaseMenuObject(MenuObject);
            RETURN( Ret);
         }

      case TWOPARAM_ROUTINE_SETGUITHRDHANDLE:
         {
            PUSER_MESSAGE_QUEUE MsgQueue = ((PTHREADINFO)PsGetCurrentThread()->Tcb.Win32Thread)->MessageQueue;

            ASSERT(MsgQueue);
            RETURN( (DWORD_PTR)MsqSetStateWindow(MsgQueue, (ULONG)Param1, (HWND)Param2));
         }

      case TWOPARAM_ROUTINE_ENABLEWINDOW:
         RETURN( IntEnableWindow((HWND)Param1, (BOOL)Param2));

      case TWOPARAM_ROUTINE_SHOWOWNEDPOPUPS:
      {
         Window = UserGetWindowObject((HWND)Param1);
         if (!Window) RETURN(0);

         RETURN( (DWORD_PTR)IntShowOwnedPopups(Window, (BOOL) Param2));
      }

      case TWOPARAM_ROUTINE_ROS_UPDATEUISTATE:
      {
          WPARAM wParam;
          Window = UserGetWindowObject((HWND)Param1);
          if (!Window) RETURN(0);

          /* Unpack wParam */
          wParam = MAKEWPARAM((Param2 >> 3) & 0x3,
                              Param2 & (UISF_HIDEFOCUS | UISF_HIDEACCEL | UISF_ACTIVE));

          RETURN( UserUpdateUiState(Window, wParam) );
      }

      case TWOPARAM_ROUTINE_SWITCHTOTHISWINDOW:
         STUB
         RETURN( 0);


      case TWOPARAM_ROUTINE_SETCARETPOS:
         RETURN( (DWORD_PTR)co_IntSetCaretPos((int)Param1, (int)Param2));

      case TWOPARAM_ROUTINE_REGISTERLOGONPROCESS:
         RETURN( (DWORD_PTR)co_IntRegisterLogonProcess((HANDLE)Param1, (BOOL)Param2));

      case TWOPARAM_ROUTINE_SETCURSORPOS:
         RETURN( (DWORD_PTR)UserSetCursorPos((int)Param1, (int)Param2, 0, 0, FALSE));

      case TWOPARAM_ROUTINE_UNHOOKWINDOWSHOOK:
         RETURN( IntUnhookWindowsHook((int)Param1, (HOOKPROC)Param2));
   }
   ERR("Calling invalid routine number 0x%x in NtUserCallTwoParam(), Param1=0x%x Parm2=0x%x\n",
           Routine, Param1, Param2);
   EngSetLastError(ERROR_INVALID_PARAMETER);
   RETURN( 0);

CLEANUP:
   TRACE("Leave NtUserCallTwoParam, ret=%i\n",_ret_);
   UserLeave();
   END_CLEANUP;
}