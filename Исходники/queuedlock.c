/**
 * Sets a wake event, unblocking all queued wait blocks.
 *
 * \param WakeEvent A wake event.
 * \param WaitBlock A wait block for a cancelled wait, otherwise
 * NULL.
 */
VOID FASTCALL PhfSetWakeEvent(
    __inout PPH_QUEUED_LOCK WakeEvent,
    __inout_opt PPH_QUEUED_WAIT_BLOCK WaitBlock
    )
{
    PPH_QUEUED_WAIT_BLOCK waitBlock;
    PPH_QUEUED_WAIT_BLOCK nextWaitBlock;

    // Pop all waiters and unblock them.

    waitBlock = _InterlockedExchangePointer((PPVOID)&WakeEvent->Value, NULL);

    while (waitBlock)
    {
        nextWaitBlock = waitBlock->Next;
        PhpUnblockQueuedWaitBlock(waitBlock);
        waitBlock = nextWaitBlock;
    }

    if (WaitBlock)
    {
        // We're cancelling a wait; the thread called this function instead
        // of PhfWaitForWakeEvent. This will remove all waiters from
        // the list. However, we may not have popped and unblocked the
        // cancelled wait block ourselves. Another thread may have popped all
        // waiters but not unblocked them yet at this point:
        //
        // 1. This thread: calls PhfQueueWakeEvent.
        // 2. This thread: code determines that the wait should be cancelled.
        // 3. Other thread: calls PhfSetWakeEvent and pops our wait block off.
        //    It hasn't unblocked any wait blocks yet.
        // 4. This thread: calls PhfSetWakeEvent. Since all wait blocks have
        //    been popped, we don't do anything. The caller function exits,
        //    making our wait block invalid.
        // 5. Other thread: tries to unblock our wait block. Anything could
        //    happen, since our caller already returned.
        //
        // The solution is to (always) wait for an unblock. Note that the check below
        // for the spinning flag is not required, but it is a small optimization.
        // If the wait block has been unblocked (i.e. the spinning flag is cleared),
        // then there's no danger.

        if (WaitBlock->Flags & PH_QUEUED_WAITER_SPINNING)
            PhpBlockOnQueuedWaitBlock(WaitBlock, FALSE, NULL);
    }
}