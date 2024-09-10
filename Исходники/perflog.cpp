void PerfLog::OutToPerfFile(__in_z const wchar_t *wszName, UnitOfMeasure unit, __in_opt const wchar_t *wszDescr)
{
    LIMITED_METHOD_CONTRACT;
    
    char szPrintStr[PRINT_STR_LEN];
    
    if (CommaSeparatedFormat())
    {
        if (WszWideCharToMultiByte (CP_ACP, 0, m_wszOutStr_1, -1, szPrintStr, PRINT_STR_LEN-1, 0, 0) ) {
            if (0 == WriteFile (m_hPerfLogFileHandle, szPrintStr, (DWORD)strlen(szPrintStr), &m_dwWriteByte, NULL))
                printf("ERROR: Could not write to perf log.\n");
        }
        else
            wprintf(W("ERROR: Could not do string conversion.\n"));        
    }
    else
    {
        wchar_t wszOutStr_2[PRINT_STR_LEN];
    
        // workaround. The formats for ExecTime is slightly different from a custom value.
        if (wcscmp(wszName, W("ExecTime")) == 0)
            _snwprintf_s(wszOutStr_2, PRINT_STR_LEN, PRINT_STR_LEN - 1, W("ExecUnitDescr=%s\nExecIDirection=%s\n"), wszDescr, wszIDirection[unit]);
        else
        {
            if (wszDescr)
                _snwprintf_s(wszOutStr_2, PRINT_STR_LEN, PRINT_STR_LEN - 1, W("%s Descr=%s\n%s Unit Descr=None\n%s IDirection=%s\n"), wszName, wszDescr, wszName, wszName, wszIDirection[unit]);
            else
                _snwprintf_s(wszOutStr_2, PRINT_STR_LEN, PRINT_STR_LEN - 1, W("%s Descr=None\n%s Unit Descr=None\n%s IDirection=%s\n"), wszName, wszName, wszName, wszIDirection[unit]);
        }

        // Write both pieces to the file.
        if(WszWideCharToMultiByte (CP_ACP, 0, m_wszOutStr_1, -1, szPrintStr, PRINT_STR_LEN-1, 0, 0) ) {
            if (0 == WriteFile (m_hPerfLogFileHandle, szPrintStr, (DWORD)strlen(szPrintStr), &m_dwWriteByte, NULL))
                printf("ERROR: Could not write to perf log.\n");
        } 
        else 
            wprintf(W("ERROR: Could not do string conversion.\n"));
                
        if(WszWideCharToMultiByte (CP_ACP, 0, wszOutStr_2, -1, szPrintStr, PRINT_STR_LEN-1, 0, 0)) {
            if (0 == WriteFile (m_hPerfLogFileHandle, szPrintStr, (DWORD)strlen(szPrintStr), &m_dwWriteByte, NULL))
                printf("ERROR: Could not write to perf log.\n");
        }
        else 
            wprintf(W("ERROR: Could not do string conversion.\n"));
    }
}