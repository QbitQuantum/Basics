// Replace this process' environment with the current system environment
void UpdateEnvironment()
{
    // Fetch the current environment for the user
    HANDLE accessToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_QUERY, &accessToken))
        return;

    wchar_t* environment;
    if (!CreateEnvironmentBlock((LPVOID*)&environment, accessToken, FALSE))
        return;

    // Empty the current environment
    QStringList variables;
    wchar_t* currentEnvironment = GetEnvironmentStrings();
    for (TCHAR* p = currentEnvironment; *p != 0;)
    {
        QString variable = QString::fromUtf16(p);
        QString name = variable.section("=", 0, 0);
        // Ignore entries for drive current directory entries that have no name
        if (name.size() > 0)
            variables.append(name);
        p += wcslen(p) + 1;
    }
    if (currentEnvironment)
        FreeEnvironmentStrings(currentEnvironment);

    // Now we've finished enumerating the current environment, we can safely delete variables
    foreach (QString name, variables)
    {
        SetEnvironmentVariable(name.utf16(), NULL);
    }