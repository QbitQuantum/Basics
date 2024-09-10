/****************************************************************************

Function:   ModifyMyString

Parameters: pStr : Pointer to pointer to UNICODE string

Returns:    none

Purpose:    Display the string passed in, modify it, and return

Comments:   This sample is meant to demonstrate a typical use of the
            represent_as attribute:  The client and server have different
            local views of the data, although the IDL file describes the
            wire contract.

****************************************************************************/
void ModifyMyString(IN RPC_BINDING_HANDLE hBinding,
					WCHAR_STRING * pStr)
{
    wprintf_s(L"\nModifyMyString: received UNICODE string:\n%s\n\n", *pStr );
    wcscpy_s(*pStr,wcslen(*pStr), L"This UNICODE string comes back on the wire as ASCII");
    wprintf_s(L"ModifyMyString: sending UNICODE string:\n%s\n\n", *pStr );

}