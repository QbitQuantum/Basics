LRESULT CALLBACK HostPowerServiceWin::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_POWERBROADCAST:
        {
            HostPowerServiceWin *pPowerObj;

            pPowerObj = (HostPowerServiceWin *)GetWindowLongPtr(hwnd, 0);
            if (pPowerObj)
            {
                switch(wParam)
                {
                case PBT_APMSUSPEND:
                    pPowerObj->notify(Reason_HostSuspend);
                    break;

                case PBT_APMRESUMEAUTOMATIC:
                    pPowerObj->notify(Reason_HostResume);
                    break;

                case PBT_APMPOWERSTATUSCHANGE:
                {
                    SYSTEM_POWER_STATUS SystemPowerStatus;

                    Log(("PBT_APMPOWERSTATUSCHANGE\n"));
                    if (GetSystemPowerStatus(&SystemPowerStatus) == TRUE)
                    {
                        Log(("PBT_APMPOWERSTATUSCHANGE ACLineStatus=%d BatteryFlag=%d\n", SystemPowerStatus.ACLineStatus,
                             SystemPowerStatus.BatteryFlag));

                        if (SystemPowerStatus.ACLineStatus == 0)      /* offline */
                        {
                            if (SystemPowerStatus.BatteryFlag == 2 /* low > 33% */)
                            {
                                LONG rc;
                                SYSTEM_BATTERY_STATE BatteryState;

                                rc = CallNtPowerInformation(SystemBatteryState, NULL, 0, (PVOID)&BatteryState,
                                                            sizeof(BatteryState));
#ifdef LOG_ENABLED
                                if (rc == 0 /* STATUS_SUCCESS */)
                                    Log(("CallNtPowerInformation claims %d seconds of power left\n",
                                         BatteryState.EstimatedTime));
#endif
                                if (    rc == 0 /* STATUS_SUCCESS */
                                    &&  BatteryState.EstimatedTime < 60*5)
                                {
                                    pPowerObj->notify(Reason_HostBatteryLow);
                                }
                            }
                            else
                            /* If the machine has less than 5% battery left (and is not connected
                             * to the AC), then we should save the state. */
                            if (SystemPowerStatus.BatteryFlag == 4      /* critical battery status; less than 5% */)
                            {
                                pPowerObj->notify(Reason_HostBatteryLow);
                            }
                        }
                    }
                    break;
                }
                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
            }
            return TRUE;
        }

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}