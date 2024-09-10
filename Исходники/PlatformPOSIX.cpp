std::string
PlatformPOSIX::GetPlatformSpecificConnectionInformation()
{
    StreamString stream;
    if (GetSupportsRSync())
    {
        stream.PutCString("rsync");
        if ( (GetRSyncOpts() && *GetRSyncOpts()) ||
             (GetRSyncPrefix() && *GetRSyncPrefix()) ||
             GetIgnoresRemoteHostname())
        {
            stream.Printf(", options: ");
            if (GetRSyncOpts() && *GetRSyncOpts())
                stream.Printf("'%s' ",GetRSyncOpts());
            stream.Printf(", prefix: ");
            if (GetRSyncPrefix() && *GetRSyncPrefix())
                stream.Printf("'%s' ",GetRSyncPrefix());
            if (GetIgnoresRemoteHostname())
                stream.Printf("ignore remote-hostname ");
        }
    }
    if (GetSupportsSSH())
    {
        stream.PutCString("ssh");
        if (GetSSHOpts() && *GetSSHOpts())
            stream.Printf(", options: '%s' ",GetSSHOpts());
    }
    if (GetLocalCacheDirectory() && *GetLocalCacheDirectory())
        stream.Printf("cache dir: %s",GetLocalCacheDirectory());
    if (stream.GetSize())
        return stream.GetData();
    else
        return "";
}