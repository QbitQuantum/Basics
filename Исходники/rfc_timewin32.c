// Sets this date as the current system date and time
int32_t rfDate_SetToSystem(RF_Date* d)
{
    SYSTEMTIME st;
    RF_DATE_TO_SYSTEMTIME(d,st)

    if(SetSystemTime(&st) == 0)
    {
        RF_WIN32_GETSYSERROR(strBuff)
        LOG_ERROR("Setting the system time from an RF_Date in Windows failed with Windows Error(%lu):\n%s",RE_DATE_SET_SYSTEMTIME,i_ERROR_CODE,strBuff);
        LocalFree(strBuff);
        return RF_FAILURE;
    }
    return RF_SUCCESS;
}