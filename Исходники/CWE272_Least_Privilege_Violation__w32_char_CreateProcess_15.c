void CWE272_Least_Privilege_Violation__w32_char_CreateProcess_15_bad()
{
    switch(6)
    {
    case 6:
    {
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        /* FLAW: The commandLine parameter to CreateProcess() contains a space in it and does not
           surround the executable path with quotes.  A malicious executable could be run because
           of the way the function parses spaces. The process will attempt to run "Program.exe,"
           if it exists, instead of the intended "GoodApp.exe" */
        if( !CreateProcessA(NULL,
                            "C:\\Program Files\\GoodApp arg1 arg2",
                            NULL,
                            NULL,
                            FALSE,
                            0,
                            NULL,
                            NULL,
                            &si,
                            &pi))
        {
            printLine("CreateProcess failed");
            return;
        }
        else
        {
            printLine("CreateProcess successful");
        }
        /* Wait until child process exits. */
        WaitForSingleObject(pi.hProcess, INFINITE);
        /* Close process and thread handles.*/
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    break;
    default:
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
        break;
    }
}