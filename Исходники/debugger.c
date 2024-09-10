/***********************************************************************
 *           OutputDebugStringW   (KERNEL32.@)
 *
 *  Output by an application of a unicode string to a debugger (if attached)
 *  and program log.
 *
 * PARAMS
 *  str [I] The message to be logged and given to the debugger.
 *
 * RETURNS
 *
 *  Nothing.
 */
void WINAPI OutputDebugStringW( LPCWSTR str )
{
    UNICODE_STRING strW;
    STRING strA;

    RtlInitUnicodeString( &strW, str );
    if (!RtlUnicodeStringToAnsiString( &strA, &strW, TRUE ))
    {
        OutputDebugStringA( strA.Buffer );
        RtlFreeAnsiString( &strA );
    }
}