static Error
ForwardPortWithAdb (uint16_t port, std::string& device_id)
{
    Log *log(GetLogIfAllCategoriesSet (LIBLLDB_LOG_PLATFORM));

    AdbClient adb;
    auto error = AdbClient::CreateByDeviceID(device_id, adb);
    if (error.Fail ())
        return error;

    device_id = adb.GetDeviceID();
    if (log)
        log->Printf("Connected to Android device \"%s\"", device_id.c_str ());

    return adb.SetPortForwarding(port);
}