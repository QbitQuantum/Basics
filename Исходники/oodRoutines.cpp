/** winTimer()
 *
 *  The classic Rexx external function, WinTimer() was documented prior to 4.0.0
 *  and therefore needs to be retained for backward compatibility.
 *
 *  The original implementation was poor, using SetTimer() / KillTimer().  For
 *  the wait mode, it used this loop:
 *
 *  else if ( stricmp("WAIT", mode) == 0 )
 *  {
 *      while ( !PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_REMOVE)
 *      {
 *          ; // do nothing
 *      }
 *      return 0;
 *  }
 *
 *  PeekMessage() returns immediately if there are no messages.  Since there
 *  were probably no windows on the thread, the WAIT function spun in a busy
 *  loop consuming 100% of the CPU.
 *
 *  svn revision 8968 and previous contains the original implementation if there
 *  is a need to review that code.
 *
 *  The original implmentation was replaced in ooDialog 4.2.2 with this
 *  implementation using waitable timers instead.  It is backwards compatible
 *  with the original implementation, and needs to remain that way.
 *
 *  For very small periods, SetTimer replaces the specified time with
 *  USER_TIMER_MINIMUM.  So when Rexx programmers specified 1 or 2 or 6
 *  milliseconds, the got USER_TIMER_MINIMUM instead.  We mimic that behaviour
 *  here, otherwise programs using a delay of 1 millisecond do not work the
 *  same.  We actually use 1.5 times USER_TIMER_MINIMUM because it seems to work
 *  the best.
 *
 *  @param  mode    Keyword for what is to be done.  START creates the timer and
 *                  starts it.  WAIT waits on the timer.  STOP destroys the
 *                  timer.
 *
 *  @param  msOrId  Either the period of the timer, in miliseconds, if mode is
 *                  START, or the timer ID for the other modes.
 *
 *  @return The timer ID for the START mode, or success / error return code for
 *          the  other modes.
 *
 *  @notes  Sets the .SystemErrorCode.  For the STOP and WAIT modes the system
 *          error code value is returned in addition to setting the
 *          .SystemErrorCode.
 *
 *  @remarks  If this routine was being implemented from scratch, it would be
 *            done differently.  However since it is being used to preserve
 *            backwards compatibility, this implementation serves best.  An
 *            enhancement creating a new Waitable object class would be nice.
 */
RexxRoutine2(uintptr_t, winTimer_rtn, CSTRING, mode, uintptr_t, msOrId)
{
    oodResetSysErrCode(context->threadContext);

    if ( stricmp("START", mode) == 0 )
    {
        HANDLE hTimer = NULL;
        LARGE_INTEGER liDueTime;

        if ( msOrId < USER_TIMER_MINIMUM + 5 )
        {
            msOrId = USER_TIMER_MINIMUM + 5;
        }

        liDueTime.QuadPart = msOrId * -10000;

        hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
        if ( hTimer == NULL )
        {
            oodSetSysErrCode(context->threadContext);
            return 0;
        }

        if ( ! SetWaitableTimer(hTimer, &liDueTime, (int32_t)msOrId, NULL, NULL, FALSE) )
        {
            oodSetSysErrCode(context->threadContext);
            return 0;
        }

        return (uintptr_t)hTimer;
    }
    else if ( stricmp("STOP", mode) == 0 )
    {
        if ( CancelWaitableTimer((HANDLE)msOrId) == 0 )
        {
            uint32_t rc = GetLastError();
            oodSetSysErrCode(context->threadContext, rc);
            return rc;
        }
        return 0;
    }
    else if ( stricmp("WAIT", mode) == 0 )
    {
        if ( WaitForSingleObject((HANDLE)msOrId, INFINITE) != WAIT_OBJECT_0 )
        {
            uint32_t rc = GetLastError();
            oodSetSysErrCode(context->threadContext, rc);
            return rc;
        }
        return 0;
    }

    wrongArgValueException(context->threadContext, 1, "START, STOP, WAIT", mode);
    return 0;
}