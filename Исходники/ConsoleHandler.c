void resetDefaultHandlers(void)
{
    if ( !SetConsoleCtrlHandler(shutdown_handler, false) ) {
        errorBelch("warning: failed to uninstall default console handler");
    }
}