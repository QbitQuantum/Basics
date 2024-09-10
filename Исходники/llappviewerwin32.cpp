void LLAppViewerWin32::handleCrashReporting()
{
    // Windows only behaivor. Spawn win crash reporter.
    std::string exe_path = gDirUtilp->getAppRODataDir();
    exe_path += gDirUtilp->getDirDelimiter();
    exe_path += "win_crash_logger.exe";

    std::string arg_string = "-user ";
    arg_string += gGridName;

    switch(getCrashBehavior())
    {
    case CRASH_BEHAVIOR_ASK:
    default:
        arg_string += " -dialog ";
        _spawnl(_P_NOWAIT, exe_path.c_str(), exe_path.c_str(), arg_string.c_str(), NULL);
        break;

    case CRASH_BEHAVIOR_ALWAYS_SEND:
        _spawnl(_P_NOWAIT, exe_path.c_str(), exe_path.c_str(), arg_string.c_str(), NULL);
        break;

    case CRASH_BEHAVIOR_NEVER_SEND:
        break;
    }
}