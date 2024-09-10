bool_t CC_CALL sys_get_power_info(CC_POWER_STATE_ENUM *state, dword_t *seconds, byte_t *percent)
{
    SYSTEM_POWER_STATUS status;
    bool_t need_details = FALSE;

    /* This API should exist back to Win95. */
    if (!GetSystemPowerStatus(&status)) {
        /* !!! FIXME: push GetLastError() */
        *state = CC_POWERSTATE_UNKNOWN;
    } else if (status.BatteryFlag == 0xFF) {/* unknown state */
        *state = CC_POWERSTATE_UNKNOWN;
    } else if (status.BatteryFlag & (1 << 7)) {/* no battery */
        *state = CC_POWERSTATE_NO_BATTERY;
    } else if (status.BatteryFlag & (1 << 3)) {/* charging */
        *state = CC_POWERSTATE_CHARGING;
        need_details = TRUE;
    } else if (status.ACLineStatus == 1) {/* on AC, not charging. */
        *state = CC_POWERSTATE_CHARGED;
        need_details = TRUE;
    } else {
        *state = CC_POWERSTATE_ON_BATTERY;/* not on AC. */
        need_details = TRUE;
    }

    *percent = -1;
    *seconds = -1;

    if (need_details) {
        const byte_t pct = (byte_t)status.BatteryLifePercent;
        const dword_t secs = (dword_t)status.BatteryLifeTime;
        /* 255 == unknown */
        if (pct != 0xFF) {
            /* clamp between 0%, 100% */
            *percent = (pct > 100) ? 100 : pct; 
        }
        /* ((DWORD)-1) == unknown */
        if (secs != 0xFFFFFFFF) {
            *seconds = secs;
        }
    }
    /* always the definitive answer on Windows. */
    return TRUE;
}