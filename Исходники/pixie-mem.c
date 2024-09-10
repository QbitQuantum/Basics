void win_perror(const char *str)
{
    DWORD dwError = GetLastError();
    LPVOID lpvMessageBuffer;

    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, dwError,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPSTR)&lpvMessageBuffer, 0, NULL);

    //... now display this string
    fprintf(stderr, "%s: %s\n", str, lpvMessageBuffer);

    
    // Free the buffer allocated by the system
    LocalFree(lpvMessageBuffer);

}