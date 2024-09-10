    PLUGIN_FUNCTION_ARG3(GetDeviceName,unsigned,index, char *,buffer, unsigned,bufsize)
    {
        if (buffer == NULL || bufsize < 4)
            return PluginLID_InvalidParameter;

        if (index >= 1)
            return PluginLID_NoMoreNames;

        if (StartDeviceDetection(NULL, 0, 0, 0, 0, 0, 0, 0, 0) == 0)
            return PluginLID_NoMoreNames;

        CloseDevice();

        UINT numDevs = waveOutGetNumDevs();
        for (UINT i = 0; i < numDevs; i++) {
            WAVEOUTCAPS caps;
            waveOutGetDevCaps(i, &caps, sizeof(caps));
            if (strstr(caps.szPname, "USB Audio") != NULL) {
                if (bufsize <= strlen(caps.szPname))
                    return PluginLID_BufferTooSmall;

                int pos = strlen(caps.szPname)-1;
                while (caps.szPname[pos] == ' ')
                    caps.szPname[pos--] = '\0';
                strcpy(buffer, caps.szPname);
                return PluginLID_NoError;
            }
        }

        return PluginLID_NoMoreNames;
    }