void remove_ctrlc(void)
{
    SetConsoleCtrlHandler( handle_ctrlc, FALSE );
}