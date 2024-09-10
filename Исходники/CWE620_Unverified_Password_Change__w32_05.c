/* good1() uses if(staticFalse) instead of if(staticTrue) */
static void good1()
{
    if(staticFalse)
    {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    }
    else
    {
        {
            wchar_t oldPassword[256];
            wchar_t newPassword[256];
            NET_API_STATUS status;
            printWLine(L"Enter old password: "******"%255s", oldPassword) != 1)
            {
                oldPassword[0] = L'\0';
            }
            printWLine(L"Enter new password: "******"%255s", newPassword) != 1)
            {
                newPassword[0] = L'\0';
            }
            /* FIX: Verify the old password when setting the new password */
            status = NetUserChangePassword(NULL, USERNAME, oldPassword, newPassword);
            if(status == NERR_Success)
            {
                printWLine(L"Success!");
            }
            else
            {
                wprintf(L"NetUserChangePassword failed.  Status = %u = 0x%x\n", status, status);
            }
        }
    }
}