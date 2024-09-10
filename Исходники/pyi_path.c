/*
 * Return full path to the current executable.
 * Executable is the .exe created by pyinstaller: path/myappname.exe
 *
 * execfile - buffer where to put path to executable.
 * appname - usually the item argv[0].
 */
int pyi_path_executable(char *execfile, const char *appname)
{
    char buffer[PATH_MAX];

#ifdef WIN32
    char dos83_buffer[PATH_MAX];
    stb__wchar wchar_buffer[PATH_MAX];
    stb__wchar wchar_dos83_buffer[PATH_MAX];
    char basename[PATH_MAX];
    char dirname[PATH_MAX];

    /* Windows has special function to obtain path to executable.
     * We EXPLICTLY use wide-string API in the bootloader because
     * otherwise it is impossible to represent non-ASCII character
     * from a different character set. For instance, let's say I have
     * a Latin-1 (Europe Windows), and I want to run a PyInstaller
     * program in a path with japanese character; there is no way to
     * represent that path with ANSI API in Windows, because ANSI API
     * would only support the local charset (Latin-1).
     */
	if (!GetModuleFileNameW(NULL, wchar_buffer, PATH_MAX)) {
		FATALERROR("System error - unable to load!");
		return -1;
	}
    /* Convert wchar_t to utf8. Just use type char as usual. */
    stb_to_utf8(buffer, wchar_buffer, PATH_MAX);

    /*
     * Use 8.3 filename (dos 8.3 or short filename)
     * to overcome the Python and PyInstaller limitation
     * to run with foreign characters in directory names.
     *
     * If 8.3 filename does not exist, original vaule is just copied
     * to the supplied buffer. 8.3 filename might not be available
     * for some networking file systems.
     *
     * This is workaround for <http://www.pyinstaller.org/ticket/298>.
     */
    GetShortPathNameW(wchar_buffer, wchar_dos83_buffer, PATH_MAX);
    /* Convert wchar_t to utf8 just use char as usual. */
    stb_to_utf8(dos83_buffer, wchar_dos83_buffer, PATH_MAX);

    /*
     * Construct proper execfile -  83_DIRNAME + full_basename.
     * GetShortPathName() makes also the basename (appname.exe) shorter.
     *
     * However, bootloader code depends on unmodified basename.
     * Using basename from original path should fix this.
     * It is supposed that basename does not contain any foreign characters.
     *
     * Reuse 'buffer' variable.
     */
    pyi_path_basename(basename, buffer);
    pyi_path_dirname(dirname, dos83_buffer);
    pyi_path_join(buffer, dirname, basename);

#elif __APPLE__
    uint32_t length = sizeof(buffer);

    /* Mac OS X has special function to obtain path to executable. */
    if (_NSGetExecutablePath(buffer, &length) != 0) {
        FATALERROR("System error - unable to load!");
		return -1;
    }
#else
    /* Fill in thisfile. */
    #ifdef __CYGWIN__
    if (strncasecmp(&appname[strlen(appname)-4], ".exe", 4)) {
        strcpy(execfile, appname);
        strcat(execfile, ".exe");
        PI_SetProgramName(execfile);
    }
    else
    #endif /* __CYGWIN__ */
    PI_SetProgramName(appname);
    strcpy(buffer, PI_GetProgramFullPath());
#endif
    /*
     * Ensure path to executable is absolute.
     * 'execfile' starting with ./ might break some modules when changing
     * the CWD.From 'execfile' is constructed 'homepath' and homepath is used
     * for LD_LIBRARY_PATH variavle. Relative LD_LIBRARY_PATH is a security
     * problem.
     */
    if(stb_fullpath(execfile, PATH_MAX, buffer) == false) {
        VS("LOADER: executable is %s\n", execfile);
        return -1;
    }
 
    VS("LOADER: executable is %s\n", execfile);

	return 0;
}