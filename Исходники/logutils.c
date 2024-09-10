PDH_FUNCTION
WriteTextLogHeader (
    IN  PLOG_INFO   pLog
)
{
    LONG      pdhStatus = ERROR_SUCCESS;
    PLOG_COUNTER_INFO   pThisCounter;
    CHAR            cDelim;
    CHAR            szLeadDelim[4];
    DWORD           dwLeadSize;
    CHAR            szTrailDelim[4];
    DWORD           dwTrailSize;
    DWORD           dwBytesWritten;
    PPDH_COUNTER_INFO_A  pCtrInfo;
    DWORD           dwCtrInfoSize;
    BOOL            bResult;

    pCtrInfo = G_ALLOC (8192);

    if (pCtrInfo == NULL) {
        return PDH_MEMORY_ALLOCATION_FAILURE;
    }

    cDelim = (LOWORD(pLog->dwLogFormat) == OPD_CSV_FILE) ? COMMA_DELIMITER :
            TAB_DELIMITER;

    szLeadDelim[0] = cDelim;
    szLeadDelim[1] = DOUBLE_QUOTE;
    szLeadDelim[2] = 0;
    szLeadDelim[3] = 0;
    dwLeadSize = 2;

    szTrailDelim[0] = DOUBLE_QUOTE;
    szTrailDelim[1] = 0;
    szTrailDelim[2] = 0;
    szTrailDelim[3] = 0;
    dwTrailSize = 1;


    // write the logfile header record
    bResult = WriteFile (pLog->hLogFileHandle,
        (LPCVOID)&szTrailDelim[0],
        1,
        &dwBytesWritten,
        NULL);

    if (!bResult) {
        pdhStatus = GetLastError();
    }

    if (pdhStatus == ERROR_SUCCESS) {
        // write the time stamp title
        bResult = WriteFile (pLog->hLogFileHandle,
            (LPCVOID)szTimeStampLabel,
            dwTimeStampLabelLength,
            &dwBytesWritten,
            NULL);

        if (!bResult) {
            pdhStatus = GetLastError();
        }
    }

    if (pdhStatus == ERROR_SUCCESS) {
        // check each counter in the list of counters for this query and
        // write them to the file

        // output the path names
        pThisCounter = pFirstCounter;

        if (pThisCounter != NULL) {
            do {
                // write  the leading delimiter
                bResult = WriteFile (pLog->hLogFileHandle,
                    (LPCVOID)szLeadDelim,
                    dwLeadSize,
                    &dwBytesWritten,
                    NULL);

                if (!bResult) {
                    pdhStatus = GetLastError();
                    break; // out of the Do Loop
                }

                // get the counter path information from the counter
                dwCtrInfoSize = 8192;
                pdhStatus = PdhGetCounterInfoA (
                    pThisCounter->hCounter,
                    FALSE,
                    &dwCtrInfoSize,
                    pCtrInfo);

                if (pdhStatus == ERROR_SUCCESS) {
                    // write the counter name
                    bResult = WriteFile (pLog->hLogFileHandle,
                        (LPCVOID)pCtrInfo->szFullPath,
                        lstrlen(pCtrInfo->szFullPath),
                        &dwBytesWritten,
                        NULL);

                    if (!bResult) {
                        pdhStatus = GetLastError();
                        break; // out of the Do Loop
                    }
                } else {
                    // unable to get counter information so bail here
                    break;
                }

                // write  the trailing delimiter
                bResult = WriteFile (pLog->hLogFileHandle,
                    (LPCVOID)szTrailDelim,
                    dwTrailSize,
                    &dwBytesWritten,
                    NULL);


                if (!bResult) {
                    pdhStatus = GetLastError();
                    break; // out of the Do Loop
                }

                pThisCounter = pThisCounter->next;
            } while (pThisCounter != NULL);
        }
    }

    if (pdhStatus == ERROR_SUCCESS) {
        // write  the record terminator
        bResult = WriteFile (pLog->hLogFileHandle,
            (LPCVOID)szRecordTerminator,
            dwRecordTerminatorLength,
            &dwBytesWritten,
            NULL);
        if (!bResult) {
            pdhStatus = GetLastError();
        }
    }

    G_FREE (pCtrInfo);

    return pdhStatus;
}