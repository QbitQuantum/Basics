/**
* Similar to ShellExecuteW() Win32 Shell API (shell32.dll),
* except that it will work also on Win9x/ME without MSLU support.
*
* Note: this Win32 function is also missing in the Microsoft Unicode
* Layer for Win9X/ME...
*
* Warning!
* There is no explicit size parameter for the destination buffer.
* This function may store up to 260 characters in the Result
* string, including the terminating NUL character.
*/
UAWIN32API  HINSTANCE
APIENTRY    UFindExecutable(
    LPCWSTR     lpcwszFile,         /*UTF-16 IN*/
    LPCWSTR     lpcwszDirectory,    /*UTF-16 IN*/
    LPWSTR      lpwszResult)        /*UTF-16 OUT*/
{
    HINSTANCE  hInst;
    LPSTR      lpszResult;

    static BOOL bDisable_FindExecutableW = FALSE;
    if (!bDisable_FindExecutableW &&
        isWin32UnicodeAPIsSupported()) {
        typedef HINSTANCE
            (WINAPI *FARPROC_FindExecutableW)(
            LPCWSTR     lpcwszFile,         /*UTF-16 IN*/
            LPCWSTR     lpcwszDirectory,    /*UTF-16 IN*/
            LPWSTR      lpwszResult);       /*UTF-16 OUT*/
        static FARPROC_FindExecutableW farproc_FindExecutableW =
            (FARPROC_FindExecutableW)NULL;

        if (farproc_FindExecutableW == (FARPROC_FindExecutableW)NULL) {
            HMODULE hModule = GetModuleHandleA("shell32.dll");
            farproc_FindExecutableW = (FARPROC_FindExecutableW)
                GetProcAddress(hModule, "FindExecutableW");
        }
        if (farproc_FindExecutableW != (FARPROC_FindExecutableW)NULL) {
            return (*farproc_FindExecutableW)(
                lpcwszFile,         /*UTF-16 IN*/
                lpcwszDirectory,    /*UTF-16 IN*/
                lpwszResult);       /*UTF-16 OUT*/
        }
        bDisable_FindExecutableW = TRUE;
    }
    /* Convert UTF-16 input strings to ANSI */
    LPCWSTR_TO_LPSTR(lpcwszFile,
        return (HINSTANCE)SE_ERR_ASSOCINCOMPLETE
        );
    LPCWSTR_TO_LPSTR(lpcwszDirectory,
        return (HINSTANCE)SE_ERR_ASSOCINCOMPLETE
        );
    /* Prepare temporary ANSI output strings */
    ALLOCA_LPSTR(lpszResult, _MAX_PATH,
        return (HINSTANCE)SE_ERR_OOM
        );
    /* Execute the ANSI API */
    hInst = FindExecutableA(
        (LPCSTR)lpcwszFile,         /*ANSI IN*/
        (LPCSTR)lpcwszDirectory,    /*ANSI IN*/
        lpszResult);                /*ANSI OUT*/
    /* On success, convert temporary output strings to UTF-16 */
    if ((int)hInst > 32) {
        LPWSTR_FROM_LPCSTR(lpszResult, lpwszResult, _MAX_PATH,
            return (HINSTANCE)SE_ERR_OOM
            );
    }