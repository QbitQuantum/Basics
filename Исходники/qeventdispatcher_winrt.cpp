    bool removeTimer(int id)
    {
        if (id >= timerInfos.size())
            return false;

        WinRTTimerInfo &info = timerInfos[id];
        if (info.timerId == INVALID_TIMER_ID)
            return false;

        if (info.interval > 0 && (!timerIdToHandle.contains(id) || !timerIdToCancelHandle.contains(id)))
            return false;

        info.timerId = INVALID_TIMER_ID;

        // Remove invalid timerinfos from the vector's end, if the timer with the highest id was removed
        int lastTimer = timerInfos.size() - 1;
        while (lastTimer >= 0 && timerInfos.at(lastTimer).timerId == INVALID_TIMER_ID)
            --lastTimer;
        if (lastTimer >= 0 && lastTimer != timerInfos.size() - 1)
            timerInfos.resize(lastTimer + 1);
        timerIdToObject.remove(id);
        // ... remove handle from all lists
        if (info.interval > 0) {
            HANDLE handle = timerIdToHandle.take(id);
            timerHandleToId.remove(handle);
            SetEvent(timerIdToCancelHandle.take(id));
        }
        return true;
    }