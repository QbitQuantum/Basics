void ALDeviceList::Enumerate()
{
    char *devices;
    int major, minor, index;
    const char *actualDeviceName;

    Msg("SOUND: OpenAL: enumerate devices...");
    // have a set of vectors storing the device list, selection status, spec version #, and XRAM support status
    // -- empty all the lists and reserve space for 10 devices
    m_devices.clear				();

    CoUninitialize();
    // grab function pointers for 1.0-API functions, and if successful proceed to enumerate all devices
    if (alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT"))
    {
        Msg("SOUND: OpenAL: EnumerationExtension Present");

        devices				= (char *)alcGetString(NULL, ALC_DEVICE_SPECIFIER);
        Msg					("devices %s",devices);
        m_defaultDeviceName	= (char *)alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
        Msg("SOUND: OpenAL: system  default SndDevice name is %s", m_defaultDeviceName.c_str());

        // ManowaR
        // "Generic Hardware" device on software AC'97 codecs introduce
        // high CPU usage ( up to 30% ) as a consequence - freezes, FPS drop
        // So if default device is "Generic Hardware" which maps to DirectSound3D interface
        // We re-assign it to "Generic Software" to get use of old good DirectSound interface
        // This makes 3D-sound processing unusable on cheap AC'97 codecs
        // Also we assume that if "Generic Hardware" exists, than "Generic Software" is also exists
        // Maybe wrong

        if(0==stricmp(m_defaultDeviceName.c_str(),AL_GENERIC_HARDWARE))
        {
            m_defaultDeviceName			= AL_GENERIC_SOFTWARE;
            Msg("SOUND: OpenAL: default SndDevice name set to %s", m_defaultDeviceName.c_str());
        }

        index				= 0;
        // go through device list (each device terminated with a single NULL, list terminated with double NULL)
        while (*devices != NULL)
        {
            ALCdevice *device		= alcOpenDevice(devices);
            if (device)
            {
                ALCcontext *context = alcCreateContext(device, NULL);
                if (context)
                {
                    alcMakeContextCurrent(context);
                    // if new actual device name isn't already in the list, then add it...
                    actualDeviceName = alcGetString(device, ALC_DEVICE_SPECIFIER);

                    if ( (actualDeviceName != NULL) && xr_strlen(actualDeviceName)>0 )
                    {
                        alcGetIntegerv					(device, ALC_MAJOR_VERSION, sizeof(int), &major);
                        alcGetIntegerv					(device, ALC_MINOR_VERSION, sizeof(int), &minor);
                        m_devices.push_back				(ALDeviceDesc(actualDeviceName,minor,major));
                        m_devices.back().xram			= (alIsExtensionPresent("EAX-RAM") == TRUE);
                        m_devices.back().eax			= (alIsExtensionPresent("EAX2.0") == TRUE);
                        // KD: disable unwanted eax flag to force eax on all devices
                        m_devices.back().eax_unwanted	= 0;/*((0==xr_strcmp(actualDeviceName,AL_GENERIC_HARDWARE))||
														   (0==xr_strcmp(actualDeviceName,AL_GENERIC_SOFTWARE)));*/
                        ++index;
                    }
                    alcDestroyContext(context);
                } else
                    Msg("SOUND: OpenAL: cant create context for %s",device);
                alcCloseDevice(device);
            } else
                Msg("SOUND: OpenAL: cant open device %s",devices);

            devices		+= xr_strlen(devices) + 1;
        }
    } else
        Msg("SOUND: OpenAL: EnumerationExtension NOT Present");

    ResetFilters();

    if(0!=GetNumDevices())
        Msg("SOUND: OpenAL: All available devices:");

    int majorVersion, minorVersion;
    for (int i = 0; i < GetNumDevices(); i++)
    {
        GetDeviceVersion		(i, &majorVersion, &minorVersion);
        Msg	("%d. %s, Spec Version %d.%d %s",
             i+1,
             GetDeviceName(i).c_str(),
             majorVersion,
             minorVersion,
             (GetDeviceName(i)==m_defaultDeviceName)? "(default)":"" );
    }
    CoInitializeEx (NULL, COINIT_MULTITHREADED);
}