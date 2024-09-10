int
AppUtilWindows::run(int argc, char** argv)
{
    if (!IsWindowsXPSP3OrGreater()) {
        throw std::runtime_error("Synergy only supports Windows XP SP3 and above.");
    }

    // record window instance for tray icon, etc
    ArchMiscWindows::setInstanceWin32(GetModuleHandle(NULL));

    MSWindowsScreen::init(ArchMiscWindows::instanceWin32());
    Thread::getCurrentThread().setPriority(-14);

    StartupFunc startup;
    if (ArchMiscWindows::wasLaunchedAsService()) {
        startup = &daemonNTStartupStatic;
    } else {
        startup = &foregroundStartupStatic;
        app().argsBase().m_daemon = false;
    }

    return app().runInner(argc, argv, NULL, startup);
}