void setup_test_environment()
{
#if defined _WIN32
#   if defined _MSC_VER
    _set_abort_behavior( 0, _WRITE_ABORT_MSG);
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
#   endif
#endif
#if defined __MVS__
    // z/OS UNIX System Services: Ignore SIGPIPE during test runs, as a
    // workaround for no SO_NOGSIGPIPE socket option.
    signal(SIGPIPE, SIG_IGN);
#endif
}