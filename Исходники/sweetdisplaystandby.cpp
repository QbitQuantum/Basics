void SweetDisplayStandby::timerTick()
{
    LASTINPUTINFO LastInput = {};
    LastInput.cbSize = sizeof(LastInput);
    GetLastInputInfo(&LastInput);
    int idleTime = (GetTickCount() - LastInput.dwTime) / 1000;

    if (idleTime>displayOffTime || forceDisplayTurnOff)
    {
        if (!displayWasTurnedOff)
        {
            EXECUTION_STATE cap;
            NTSTATUS status;
            status = CallNtPowerInformation(SystemExecutionState, NULL, 0, &cap, sizeof(cap));
            if (!(cap & ES_DISPLAY_REQUIRED))
            {
                addToQueue("turnOff");
                displayWasTurnedOff = true;
                //lastInputTime = LastInput.dwTime;
            }
        }
        forceDisplayTurnOff = false;
    }
    else if (idleTime>displayDimTime && enableBrighnessManagement)
    {
        if (!displayWasDimmed)
        {
            EXECUTION_STATE cap;
            NTSTATUS status;
            status = CallNtPowerInformation(SystemExecutionState, NULL, 0, &cap, sizeof(cap));
            if (!(cap & ES_DISPLAY_REQUIRED))
            {
                addToQueue("dim");
                displayWasDimmed = true;
            }
        }
    }
    else if (LastInput.dwTime > lastInputTime)
    {
        if (displayWasTurnedOff)
        {
            addToQueue("turnOn");
            displayWasTurnedOff = false;
        }
        if (displayWasDimmed)
        {
            addToQueue("illuminate");
            displayWasDimmed = false;
        }
        lastInputTime = LastInput.dwTime + 1000; //Give async function more time
    }
}