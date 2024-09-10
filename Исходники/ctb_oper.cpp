void CTB_unlink(char *name)
{
    char str[MAXPATH], *p = ctb_last_punct(name);

    if (p)
        *p = '\0';

    STRCPY(str, name);
    STRCAT(str, ".CTB");
    UNLINK(str);
    STRCPY(str, name);
    STRCAT(str, ".IND");
    UNLINK(str);
    return;
}