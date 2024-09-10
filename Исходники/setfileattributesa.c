/* this cleanup method tries to revert the file back to its initial attributes */
void do_cleanup(char* filename, DWORD attributes)
{
    DWORD result;
    result = SetFileAttributesA(filename, attributes);
    if (result == 0)
    {
        Fail("ERROR:SetFileAttributesA returned 0,failure in the do_cleanup "
             "method when trying to revert the file back to its initial attributes (%u)", GetLastError());
    }
}