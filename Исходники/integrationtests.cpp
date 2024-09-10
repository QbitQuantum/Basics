IntegrationTestFixture::IntegrationTestFixture()
{
    // TODO fix this when we have an encapsulation layer for handling
    // environment variables
#ifdef GMX_NATIVE_WINDOWS
    _putenv_s("GMX_MAXBACKUP", s_maxBackup.c_str());
#else
    setenv("GMX_MAXBACKUP", s_maxBackup.c_str(), true);
#endif
}