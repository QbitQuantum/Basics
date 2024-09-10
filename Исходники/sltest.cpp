int main(int argc, char **argv)
{
    BOOL fNeedHelp = FALSE;
    BOOL fRequestExitOnClose = FALSE;

    int arg = 1;
    for (; arg < argc && (argv[arg][0] == '-' || argv[arg][0] == '/'); arg++) {
        CHAR *argn = argv[arg] + 1;
        CHAR *argp = argn;
        while (*argp && *argp != ':') {
            argp++;
        }
        if (*argp == ':') {
            *argp++ = '\0';
        }

        switch (argn[0]) {

          case 'x':                                 // Request exit on close.
          case 'X':
            fRequestExitOnClose = TRUE;
            break;

          case '?':                                 // Help.
            fNeedHelp = TRUE;
            break;

          default:
            fNeedHelp = TRUE;
            printf("SLTEST: Bad argument: %s:%s\n", argn, argp);
            break;
        }
    }

    if (fNeedHelp) {
        printf("Usage:\n"
               "    sltest.exe [options] message\n"
               "Options:\n"
               "    /x         Ask syelogd.exe to terminate when this connect closes.\n"
               "    /?         Display this help message.\n"
               "\n");
        exit(1);
    }

    SyelogOpen("sltest", SYELOG_FACILITY_APPLICATION);
    if (arg >= argc) {
        Syelog(SYELOG_SEVERITY_INFORMATION, "Hello World! [1 of 4]");
        Syelog(SYELOG_SEVERITY_INFORMATION, "Hello World! [2 of 4]");
        Syelog(SYELOG_SEVERITY_INFORMATION, "Hello World! [3 of 4]");
        Syelog(SYELOG_SEVERITY_INFORMATION, "Hello World! [4 of 4]");
    }
    else {
        CHAR Buffer[1024] = "";

        for (; arg < argc; arg++) {
            StringCchCatA(Buffer, ARRAYSIZE(Buffer), argv[arg]);
            if (arg + 1 < argc) {
                StringCchCatA(Buffer, ARRAYSIZE(Buffer), " ");
            }
        }
        Syelog(SYELOG_SEVERITY_INFORMATION, Buffer);
    }

    SyelogClose(fRequestExitOnClose);

    return 0;
}