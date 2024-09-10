const char* Cx_LogManager::TrimFileName(const char* file)
{
    ASSERT(file && *file);

#ifndef __GNUC__
    const char* name = PathFindFileNameA(file);
#else
    const char* name = file + strlen(file);
#endif
    int folder = 0;

    while (name > file)
    {
        name--;
        if ('\\' == *name || '/' == *name)
        {
            if (++folder > 2)
            {
                name++;
                break;
            }
        }
    }

    return name;
}