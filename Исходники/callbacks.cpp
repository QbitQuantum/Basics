void BackLightCallbackSlow(POWER_BROADCAST *powerBroadcast, DWORD dwUserData) {
    if (powerBroadcast == NULL || powerBroadcast->Length == 0 ||
            (powerBroadcast->Message & PBT_TRANSITION) == FALSE)
        return;

    if (powerBroadcast->Flags & POWER_STATE_UNATTENDED ||
            powerBroadcast->Flags & POWER_STATE_IDLE ||
            powerBroadcast->Flags & POWER_STATE_USERIDLE) {
        // Light is going OFF
        InterlockedExchange((LPLONG)&(*(BOOL *)dwUserData), FALSE);
    } else {
        // Light is going ON
        Device* dev = Device::self();
        _Sleep(500);

        if (dev->IsDeviceOn()) {
            DBG_TRACE(L"CallBacks.cpp BackLightCallbackSlow ON ", 5, FALSE);
            InterlockedExchange((LPLONG)&(*(BOOL *)dwUserData), TRUE);
        }
    }

    return;
}