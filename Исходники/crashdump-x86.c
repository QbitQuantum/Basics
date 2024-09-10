/* Adds the elfcorehdr= command line parameter to command line. */
static int cmdline_add_elfcorehdr(char *cmdline, unsigned long addr)
{
    int cmdlen, len, align = 1024;
    char str[30], *ptr;

    /* Passing in elfcorehdr=xxxK format. Saves space required in cmdline.
     * Ensure 1K alignment*/
    if (addr%align)
        return -1;
    addr = addr/align;
    ptr = str;
    strcpy(str, " elfcorehdr=");
    ptr += strlen(str);
    ultoa(addr, ptr);
    strcat(str, "K");
    len = strlen(str);
    cmdlen = strlen(cmdline) + len;
    if (cmdlen > (COMMAND_LINE_SIZE - 1))
        die("Command line overflow\n");
    strcat(cmdline, str);
#if 0
    printf("Command line after adding elfcorehdr\n");
    printf("%s\n", cmdline);
#endif
    return 0;
}