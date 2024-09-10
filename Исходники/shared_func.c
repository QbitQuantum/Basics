char *getExeAbsoluteFilename(const char *exeFilename, char *szAbsFilename, \
                             const int maxSize)
{
    const char *filename;
    const char *p;
    int nFileLen;
    int nPathLen;
    char cwd[256];
    char szPath[1024];

    nFileLen = strlen(exeFilename);
    if (nFileLen >= sizeof(szPath))
    {
        logError("file: "__FILE__", line: %d, " \
                 "filename length: %d is too long, exceeds %d!", \
                 __LINE__, nFileLen, (int)sizeof(szPath));
        return NULL;
    }

    p = strrchr(exeFilename, '/');
    if (p == NULL)
    {
        int i;
        char *search_paths[] = {"/bin", "/usr/bin", "/usr/local/bin"};

        *szPath = '\0';
        filename = exeFilename;
        for (i=0; i<3; i++)
        {
            snprintf(cwd, sizeof(cwd), "%s/%s", \
                     search_paths[i], filename);
            if (fileExists(cwd))
            {
                strcpy(szPath, search_paths[i]);
                break;
            }
        }

        if (*szPath == '\0')
        {
            if (!fileExists(filename))
            {
                logError("file: "__FILE__", line: %d, " \
                         "can't find exe file %s!", __LINE__, \
                         filename);
                return NULL;
            }
        }
        else
        {
            snprintf(szAbsFilename, maxSize, "%s/%s", \
                     szPath, filename);
            return szAbsFilename;
        }
    }
    else
    {
        filename = p + 1;
        nPathLen = p - exeFilename;
        memcpy(szPath, exeFilename, nPathLen);
        szPath[nPathLen] = '\0';
    }

    if (*szPath == '/')
    {
        snprintf(szAbsFilename, maxSize, "%s/%s", szPath, filename);
    }
    else
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            logError("file: "__FILE__", line: %d, " \
                     "call getcwd fail, errno: %d, error info: %s", \
                     __LINE__, errno, STRERROR(errno));
            return NULL;
        }

        nPathLen = strlen(cwd);
        if (cwd[nPathLen - 1] == '/')
        {
            cwd[nPathLen - 1] = '\0';
        }

        if (*szPath != '\0')
        {
            snprintf(szAbsFilename, maxSize, "%s/%s/%s", \
                     cwd, szPath, filename);
        }
        else
        {
            snprintf(szAbsFilename, maxSize, "%s/%s", \
                     cwd, filename);
        }
    }

    return szAbsFilename;
}