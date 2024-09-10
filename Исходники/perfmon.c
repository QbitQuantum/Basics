/******************************************************************************
 *                                                                            *
 * Comments: Get the value of a counter. If it is a rate counter,             *
 *           sleep 1 second to get the second raw value.                      *
 *                                                                            *
 ******************************************************************************/
PDH_STATUS	calculate_counter_value(const char *function, const char *counterpath, double *value)
{
    PDH_HQUERY		query;
    PDH_HCOUNTER		handle = NULL;
    PDH_STATUS		pdh_status;
    PDH_RAW_COUNTER		rawData, rawData2;
    PDH_FMT_COUNTERVALUE	counterValue;

    if (ERROR_SUCCESS != (pdh_status = zbx_PdhOpenQuery(function, &query)))
        return pdh_status;

    if (ERROR_SUCCESS != (pdh_status = zbx_PdhAddCounter(function, NULL, query, counterpath, &handle)))
        goto close_query;

    if (ERROR_SUCCESS != (pdh_status = zbx_PdhCollectQueryData(function, counterpath, query)))
        goto remove_counter;

    if (ERROR_SUCCESS != (pdh_status = zbx_PdhGetRawCounterValue(function, counterpath, handle, &rawData)))
        goto remove_counter;

    if (PDH_CSTATUS_INVALID_DATA == (pdh_status = PdhCalculateCounterFromRawValue(handle, PDH_FMT_DOUBLE |
                                     PDH_FMT_NOCAP100, &rawData, NULL, &counterValue)))
    {
        /* some (e.g., rate) counters require two raw values, MSDN lacks documentation */
        /* about what happens but tests show that PDH_CSTATUS_INVALID_DATA is returned */

        zbx_sleep(1);

        if (ERROR_SUCCESS == (pdh_status = zbx_PdhCollectQueryData(function, counterpath, query)) &&
                ERROR_SUCCESS == (pdh_status = zbx_PdhGetRawCounterValue(function, counterpath,
                                               handle, &rawData2)))
        {
            pdh_status = PdhCalculateCounterFromRawValue(handle, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100,
                         &rawData2, &rawData, &counterValue);
        }
    }

    if (ERROR_SUCCESS != pdh_status || (PDH_CSTATUS_VALID_DATA != counterValue.CStatus &&
                                        PDH_CSTATUS_NEW_DATA != counterValue.CStatus))
    {
        if (ERROR_SUCCESS == pdh_status)
            pdh_status = counterValue.CStatus;

        zabbix_log(LOG_LEVEL_DEBUG, "%s(): cannot calculate counter value '%s': %s",
                   function, counterpath, strerror_from_module(pdh_status, L"PDH.DLL"));
    }
    else
    {
        *value = counterValue.doubleValue;
    }
remove_counter:
    PdhRemoveCounter(handle);
close_query:
    PdhCloseQuery(query);

    return pdh_status;
}