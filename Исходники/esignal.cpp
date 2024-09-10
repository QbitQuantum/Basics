void enable_exit_signaller()
{
    SetConsoleCtrlHandler( control_handler, TRUE );
}