int main( int argc, char *argv [] )
{
    HINSTANCE hInstance;
    LPSTR lpszCmdParam;
    int i, len = 0;
    _ARGC = argc;
    _ARGV = (char **)argv;

    if (!(hInstance = MAIN_WinelibInit( &argc, argv ))) return 0;

    /* Alloc szCmdParam */
    for (i = 1; i < argc; i++) len += strlen(argv[i]) + 1;
    lpszCmdParam = (LPSTR) xmalloc(len + 1);
    /* Concatenate arguments */
    if (argc > 1) strcpy(lpszCmdParam, argv[1]);
    else lpszCmdParam[0] = '\0';
    for (i = 2; i < argc; i++) strcat(strcat(lpszCmdParam, " "), argv[i]);

    return WinMain (hInstance,    /* hInstance */
                    0,            /* hPrevInstance */
                    lpszCmdParam, /* lpszCmdParam */
                    SW_NORMAL);   /* nCmdShow */
}