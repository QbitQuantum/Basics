bool SystemSleep(bool hibernate)
{
    if (!GetSeShutdownNamePrivelege()) {
        std::string msg = Utilities::MakeString() << __FUNCTION__": GetSeShutdownNamePrivelege() failed.";
        BOOST_LOG_SEV(logger(), error) << msg;
        return false;
    }

    const bool force = true;
    if (!SetSuspendState(hibernate,
                         force,
                         false)
        )
    {
        DWORD last_error = GetLastError();
        std::string msg = Utilities::MakeString() << __FUNCTION__": SetSuspendState(" << hibernate << ", " << force << ", " << false << ") failed. Reason: " << last_error;
        BOOST_LOG_SEV(logger(), error) << msg;
        return false; 
    }
    return true;
}