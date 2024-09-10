/**
* @brief Get the list of paths specified in the query or the list of status values
*        for each path.
* @param id The identifier of the query information to retrieve.
* @param results The handle to a query or subscription result set.
* @param property A caller-allocated buffer that will receive the query information.
*                 The buffer contains an EVT_VARIANT object.
*
* @return returns Print event status.
*/
DWORD EventLogReader::GetQueryStatusProperty(EVT_QUERY_PROPERTY_ID id, EVT_HANDLE results, PEVT_VARIANT& property)
{
    DWORD status = ERROR_SUCCESS;
    DWORD bufferSize = 0;
    DWORD bufferUsed = 0;
    if (!EvtGetQueryInfo(results, id, bufferSize, property, &bufferUsed))
    {
        status = GetLastError();
        if (ERROR_INSUFFICIENT_BUFFER == status)
        {
            bufferSize = bufferUsed;
            property = (PEVT_VARIANT)malloc(bufferSize);
            if (property != nullptr)
            {
                EvtGetQueryInfo(results, id, bufferSize, property, &bufferUsed);
                status = GetLastError();
            }
            else
            {
                status = ERROR_OUTOFMEMORY;
            }

        }
    }
    return status;
}