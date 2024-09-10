Error
PlatformAndroid::ConnectRemote(Args& args)
{
    m_device_id.clear();

    if (IsHost())
    {
        return Error ("can't connect to the host platform '%s', always connected", GetPluginName().GetCString());
    }

    if (!m_remote_platform_sp)
        m_remote_platform_sp = PlatformSP(new PlatformAndroidRemoteGDBServer());

    int port;
    std::string scheme, host, path;
    const char *url = args.GetArgumentAtIndex(0);
    if (!url)
        return Error("URL is null.");
    if (!UriParser::Parse(url, scheme, host, port, path))
        return Error("Invalid URL: %s", url);
    if (scheme == "adb")
        m_device_id = host;

    auto error = PlatformLinux::ConnectRemote(args);
    if (error.Success())
    {
        AdbClient adb;
        error = AdbClient::CreateByDeviceID(m_device_id, adb);
        if (error.Fail())
            return error;

        m_device_id = adb.GetDeviceID();
    }
    return error;
}