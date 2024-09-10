void SmartAI::UpdatePath(const uint32 diff)
{
    if (!HasEscortState(SMART_ESCORT_ESCORTING))
        return;

    if (mEscortInvokerCheckTimer < diff)
    {
        // Xinef: Escort failed - no players in range
        // Xinef: Despawn immediately
        if (!IsEscortInvokerInRange())
        {
            StopPath(0, mEscortQuestID, true);

            // Xinef: allow to properly hook out of range despawn action, which in most cases should perform the same operation as dying
            GetScript()->ProcessEventsFor(SMART_EVENT_DEATH, me);
            me->DespawnOrUnsummon(1);
            return;
        }
        mEscortInvokerCheckTimer = 1000;
    }
    else
        mEscortInvokerCheckTimer -= diff;

    // handle pause
    if (HasEscortState(SMART_ESCORT_PAUSED))
    {
        if (mWPPauseTimer < diff)
        {
            if (!me->IsInCombat() && !HasEscortState(SMART_ESCORT_RETURNING) && (mWPReached || mForcedPaused))
            {
                GetScript()->ProcessEventsFor(SMART_EVENT_WAYPOINT_RESUMED, NULL, mCurrentWPID, GetScript()->GetPathId());
                RemoveEscortState(SMART_ESCORT_PAUSED);
                if (mForcedPaused)// if paused between 2 wps resend movement
                {
                    mWPReached = false;
                    mForcedPaused = false;
                    ResumePath();
                }

                mWPPauseTimer = 0;
            }
        }
        else
            mWPPauseTimer -= diff;
    }

    if (HasEscortState(SMART_ESCORT_RETURNING))
    {
        if (mOOCReached)//reached OOC WP
        {
            mOOCReached = false;
            RemoveEscortState(SMART_ESCORT_RETURNING);
            if (!HasEscortState(SMART_ESCORT_PAUSED))
                ResumePath();
        }
    }

    if ((me->GetVictim() && me->IsInCombat()) || HasEscortState(SMART_ESCORT_PAUSED | SMART_ESCORT_RETURNING))
        return;

    // handle next wp
    if (!me->HasUnitState(UNIT_STATE_NOT_MOVE) && me->movespline->Finalized())//reached WP
    {
        if (!mWPReached)
        {
            ResumePath();
            return;
        }

        mWPReached = false;
        if (mCurrentWPID == GetWPCount())
            EndPath();
        else if (GetNextWayPoint())
        {
            SetRun(mRun);
            // xinef: if we have reached waypoint, and there is no working spline movement it means our splitted array has ended, make new one
            if (me->movespline->Finalized())
                ResumePath();
        }
    }
}