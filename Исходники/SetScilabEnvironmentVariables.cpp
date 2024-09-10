/*--------------------------------------------------------------------------*/
static BOOL AddScilabBinDirectoryToPATHEnvironnementVariable(char *DefaultPath)
{
#define SCILAB_BIN_PATH "%s/bin"
#define NEW_PATH "PATH=%s;%s"

    BOOL bOK = FALSE;
    char *PATH = NULL;
    char *env = NULL;
    char scilabBinPath[MAX_PATH];
    char *scilabBinPathConverted;

    PATH = getenv("PATH");

    env = (char*) MALLOC(sizeof(char) * (strlen(NEW_PATH) + strlen(PATH) +
                                         strlen(DefaultPath) + 1));
    if (env)
    {
        sprintf(scilabBinPath, SCILAB_BIN_PATH, DefaultPath);

        scilabBinPathConverted = (char*) MALLOC(MAX_PATH * sizeof(char));
#ifdef _MSC_VER
        scilabBinPathConverted = strsub(scilabBinPath, "/", "\\");
#else
        scilabBinPathConverted = strdup(scilabBinPath);
#endif
        if (stristr(PATH, scilabBinPathConverted) == 0)
        {
            sprintf(env, NEW_PATH, scilabBinPathConverted, PATH);
            if (_putenv (env))
            {
                bOK = FALSE;
            }
            else
            {
                bOK = TRUE;
            }
            FREE(env);
            env = NULL;
        }

        FREE(scilabBinPathConverted);
    }
    return bOK;
}