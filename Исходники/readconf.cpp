static void
CheckConfFileHeader (const char sMagic[], const char sFile[], FILE *pFile) // in
{
char s[SLEN];
Fgets(s, SLEN-1, pFile);

int n = static_cast<int>(strlen(sMagic));
if (strncmp(s, sMagic, n) != 0) // check CONF file magic number
    {
    // truncate s at the first white space or after 20 chars
    int i;
    for (i = 0; i < n+1 && i < 20; i++)
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')
            break;
    s[i] = 0;
    Err("%s is not a %s config file\n"
        "       First part of %s is \"%s\", expected \"%s%d\"",
        sFile, sMagic, sFile, s, sMagic, CONF_FILE_VERSION);
    }
int nVersion;
if (sscanf(s+n, "%d", &nVersion) != 1)
    Err("%s has a bad header (could not read version number)", sFile);

if (nVersion != CONF_FILE_VERSION)
    Err("%s has a bad version number %d (expected %d)",
        sFile, nVersion, CONF_FILE_VERSION);
}