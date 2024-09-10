BOOL
InitializeAudioDeviceListLock()
{
    /* The security stuff is to make sure the mutex can be grabbed by
       other processes - is this the best idea though ??? */

    SECURITY_DESCRIPTOR security_descriptor;
    SECURITY_ATTRIBUTES security;

    InitializeSecurityDescriptor(&security_descriptor, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(&security_descriptor, TRUE, 0, FALSE);

    security.nLength = sizeof(SECURITY_ATTRIBUTES);
    security.lpSecurityDescriptor = &security_descriptor;
    security.bInheritHandle = FALSE;

    audio_device_list_lock = CreateMutex(&security,
                                         FALSE,
                                         AUDIO_LIST_LOCK_NAME);

    return ( audio_device_list_lock != NULL );
}