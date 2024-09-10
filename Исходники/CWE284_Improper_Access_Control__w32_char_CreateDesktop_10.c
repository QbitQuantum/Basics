void CWE284_Improper_Access_Control__w32_char_CreateDesktop_10_bad()
{
    if(globalTrue)
    {
        {
            HDESK hDesk;
            char * desktopName = "DesktopExample";
            /* FLAW: Call CreateDesktopA() with GENERIC_ALL as the 5th parameter */
            hDesk = CreateDesktopA(
                        desktopName,
                        NULL,
                        NULL,
                        0,
                        GENERIC_ALL,
                        NULL);
            if (hDesk == NULL)
            {
                printLine("Desktop could not be created");
            }
            else
            {
                printLine("Desktop created successfully");
                CloseDesktop(hDesk);
            }
        }
    }
}