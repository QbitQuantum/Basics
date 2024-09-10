DAQ_LINKAGE int daq_load_modules(const char *directory_list[])
{
    static const char *extension = MODULE_EXT;
#ifndef WIN32
    char dirpath[NAME_SIZE];
    DIR *dirp;
    struct dirent *de;
    char *p;
    int ret;

#ifdef STATIC_MODULE_LIST
    load_static_modules();
#endif

    for (; directory_list && *directory_list; directory_list++)
    {
        if (!(**directory_list))
            continue;
        if ((dirp = opendir(*directory_list)) == NULL)
        {
            fprintf(stderr,"Unable to open directory \"%s\"\n", *directory_list);
            continue;
        }

        DEBUG("Loading modules in: %s\n", *directory_list);

        while((de = readdir(dirp)) != NULL)
        {
            if (de->d_name == NULL)
                continue;
            p = strrchr(de->d_name, '.');
            if (!p || strcmp(p, extension))
                continue;
            snprintf(dirpath, sizeof(dirpath), "%s/%s", *directory_list, de->d_name);

            ret = daq_load_module(dirpath);
            if (ret == DAQ_SUCCESS)
            {
                DEBUG("Found module %s\n", de->d_name);
            }
            else if (ret == DAQ_ERROR_NOMEM)
            {
                closedir(dirp);
                return DAQ_ERROR_NOMEM;
            }
        }
        closedir(dirp);
    }
#else
    /* Find all shared library files in path */
    char path_buf[PATH_MAX];
    char dyn_lib_name[PATH_MAX];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    HANDLE fSearch;
    WIN32_FIND_DATA FindFileData;
    int pathLen = 0;
    const char *directory;
    int useDrive = 0;

#ifdef STATIC_MODULE_LIST
    load_static_modules();
#endif

    for (; directory_list && *directory_list; directory_list++)
    {
        if (!(**directory_list))
            continue;

        if ((strncpy(path_buf, *directory_list, PATH_MAX) == NULL) ||
            (strlen(path_buf) != strlen(*directory_list)))
        {
            fprintf(stderr, "Path is too long: %s\n", *directory_list);
            continue;
        }

        pathLen = strlen(path_buf);
        if ((path_buf[pathLen - 1] == '\\') ||
            (path_buf[pathLen - 1] == '/'))
        {
            /* A directory was specified with trailing dir character */
            _splitpath(path_buf, drive, dir, fname, ext);
            _makepath(path_buf, drive, dir, "*", MODULE_EXT);
            directory = &dir[0];
            useDrive = 1;
        }
        else /* A directory was specified */
        {
            _splitpath(path_buf, drive, dir, fname, ext);
            if (strcmp(extension, ""))
            {
                fprintf(stderr, "Improperly formatted directory name: %s\n", *directory_list);
                continue;
            }

            _makepath(path_buf, "", path_buf, "*", MODULE_EXT);
            directory = *directory_list;
        }

        fSearch = FindFirstFile(path_buf, &FindFileData);
        while (fSearch != NULL && fSearch != (HANDLE)-1)
        {
            if (useDrive)
                _makepath(dyn_lib_name, drive, directory, FindFileData.cFileName, NULL);
            else
                _makepath(dyn_lib_name, NULL, directory, FindFileData.cFileName, NULL);

            daq_load_module(dyn_lib_name);

            if (!FindNextFile(fSearch, &FindFileData))
            {
                break;
            }
        }
        FindClose(fSearch);
    }
#endif
    return DAQ_SUCCESS;
}