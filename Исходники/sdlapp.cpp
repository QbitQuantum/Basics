bool SDLAppAttachToConsole() {
    if(using_parent_console)      return true;
    if(gSDLAppConsoleWindow != 0) return false;

    // if TERM is set to msys, try and attach to console
    // could possibly add other supported TERMs here if there are any

    char* term = getenv("TERM");
    if(!term || strcmp(term, "msys")!=0) return false;

    if(AttachConsole(ATTACH_PARENT_PROCESS)) {

        // send stdout to console unless already redirected
        if (_fileno(stdout) == -1 || _get_osfhandle(fileno(stdout)) == -1) {
            freopen("conout$","w", stdout);
        }

        // send stderr to console unless already redirected
        if (_fileno(stderr) == -1 || _get_osfhandle(fileno(stderr)) == -1) {
            freopen("conout$","w", stderr);
        }

        using_parent_console = true;
    }

    return using_parent_console;
}