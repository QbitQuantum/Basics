static int load_vmd_library(const char *fn, t_gmxvmdplugin *vmdplugin)
{
    char            pathname[GMX_PATH_MAX], filename[GMX_PATH_MAX];
    const char     *pathenv;
    const char     *err;
    int             i;
    int             ret = 0;
    char            pathenv_buffer[GMX_PATH_MAX];
#ifndef GMX_NATIVE_WINDOWS
    glob_t          globbuf;
    const char     *defpath_suffix = "/plugins/*/molfile";
    const char     *defpathenv     = GMX_VMD_PLUGIN_PATH;
#else
    WIN32_FIND_DATA ffd;
    HANDLE          hFind = INVALID_HANDLE_VALUE;
    char            progfolder[GMX_PATH_MAX];
    char            defpathenv[GMX_PATH_MAX];
    const char     *defpath_suffix = "\\plugins\\WIN32\\molfile";
    SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES, NULL, SHGFP_TYPE_CURRENT, progfolder);
    sprintf(defpathenv, "%s\\University of Illinois\\VMD\\plugins\\WIN32\\molfile", progfolder);
#endif

    vmdplugin->api      = NULL;
    vmdplugin->filetype = strrchr(fn, '.');
    if (!vmdplugin->filetype)
    {
        return 0;
    }
    vmdplugin->filetype++;

    /* First look for an explicit path given at run time for the
     * plugins, then an implicit run-time path, and finally for one
     * given at configure time. This last might be hard-coded to the
     * default for VMD installs. */
    pathenv = getenv("VMD_PLUGIN_PATH");
    if (pathenv == NULL)
    {
        pathenv = getenv("VMDDIR");
        if (NULL == pathenv)
        {
            printf("\nNeither VMD_PLUGIN_PATH or VMDDIR set. ");
            printf("Using default location:\n%s\n", defpathenv);
            pathenv = defpathenv;
        }
        else
        {
            printf("\nVMD_PLUGIN_PATH no set, but VMDDIR is set. ");
#ifdef _MSC_VER
            _snprintf_s(pathenv_buffer, sizeof(pathenv_buffer), _TRUNCATE, "%s%s", pathenv, defpath_suffix);
#else
            snprintf(pathenv_buffer, sizeof(pathenv_buffer), "%s%s", pathenv, defpath_suffix);
#endif
            printf("Using semi-default location:\n%s\n", pathenv_buffer);
            pathenv = pathenv_buffer;
        }
    }
    strncpy(pathname, pathenv, sizeof(pathname));
#ifndef GMX_NATIVE_WINDOWS
    strcat(pathname, "/*.so");
    glob(pathname, 0, NULL, &globbuf);
    if (globbuf.gl_pathc == 0)
    {
        printf("\nNo VMD Plugins found\n"
               "Set the environment variable VMD_PLUGIN_PATH to the molfile folder within the\n"
               "VMD installation.\n"
               "The architecture (e.g. 32bit versus 64bit) of Gromacs and VMD has to match.\n");
        return 0;
    }
    for (i = 0; i < globbuf.gl_pathc && vmdplugin->api == NULL; i++)
    {
        /* FIXME: Undefined which plugin is chosen if more than one plugin
           can read a certain file ending. Requires some additional command
           line option or enviroment variable to specify which plugin should
           be picked.
         */
        ret |= load_sharedlibrary_plugins(globbuf.gl_pathv[i], vmdplugin);
    }
    globfree(&globbuf);
#else
    strcat(pathname, "\\*.so");
    hFind = FindFirstFile(pathname, &ffd);
    if (INVALID_HANDLE_VALUE == hFind)
    {
        printf("\nNo VMD Plugins found\n");
        return 0;
    }
    do
    {
        sprintf(filename, "%s\\%s", pathenv, ffd.cFileName);
        ret |= load_sharedlibrary_plugins(filename, vmdplugin);
    }
    while (FindNextFile(hFind, &ffd )  != 0 && vmdplugin->api == NULL);
    FindClose(hFind);
#endif

    if (!ret)
    {
        printf("\nCould not open any VMD library.\n");
        err = vmddlerror();
        if (!err)
        {
            printf("Compiled with dlopen?\n");
        }
        else
        {
            printf("Last error:\n%s\n", err);
        }
        return 0;
    }

    if (vmdplugin->api == NULL)
    {
        printf("\nNo plugin for %s found\n", vmdplugin->filetype);
        return 0;
    }

    if (vmdplugin->api->abiversion < 10)
    {
        printf("\nPlugin and/or VMD is too old. At least VMD 1.8.6 is required.\n");
        return 0;
    }

    printf("\nUsing VMD plugin: %s (%s)\n", vmdplugin->api->name, vmdplugin->api->prettyname);

    return 1;

}