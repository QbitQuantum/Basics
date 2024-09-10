static void
ser_windows_wait_handle (struct serial *scb, HANDLE *read, HANDLE *except)
{
    struct ser_windows_state *state;
    COMSTAT status;
    DWORD errors;
    HANDLE h = (HANDLE) _get_osfhandle (scb->fd);

    state = scb->state;

    *except = state->except_event;
    *read = state->ov.hEvent;

    if (state->in_progress)
        return;

    /* Reset the mask - we are only interested in any characters which
       arrive after this point, not characters which might have arrived
       and already been read.  */

    /* This really, really shouldn't be necessary - just the second one.
       But otherwise an internal flag for EV_RXCHAR does not get
       cleared, and we get a duplicated event, if the last batch
       of characters included at least two arriving close together.  */
    if (!SetCommMask (h, 0))
        warning (_("ser_windows_wait_handle: reseting mask failed"));

    if (!SetCommMask (h, EV_RXCHAR))
        warning (_("ser_windows_wait_handle: reseting mask failed (2)"));

    /* There's a potential race condition here; we must check cbInQue
       and not wait if that's nonzero.  */

    ClearCommError (h, &errors, &status);
    if (status.cbInQue > 0)
    {
        SetEvent (state->ov.hEvent);
        return;
    }

    state->in_progress = 1;
    ResetEvent (state->ov.hEvent);
    state->lastCommMask = -2;
    if (WaitCommEvent (h, &state->lastCommMask, &state->ov))
    {
        gdb_assert (state->lastCommMask & EV_RXCHAR);
        SetEvent (state->ov.hEvent);
    }
    else
        gdb_assert (GetLastError () == ERROR_IO_PENDING);
}