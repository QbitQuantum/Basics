std::string pcType()
{
#ifdef _WIN32
    SYSTEM_POWER_STATUS powerStatus = {};
    GetSystemPowerStatus(&powerStatus);
    if (powerStatus.BatteryFlag == 128)
        return "desktop";
    else
        return "laptop";
#else
    return "unknown";
#endif
}