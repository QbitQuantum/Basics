void initApplication(void)
{
    unsigned int channels = currentVersion->noOfChannels;
    unsigned int longKeyTime = userEeprom.getUInt16(
            currentVersion->baseAddress + 2);
    unsigned int addressStartupDelay = currentVersion->baseAddress + 4 // debounce, longTime
            + channels * 46 + channels + (11 + channels) * 4 // logic config
            + 10;
    unsigned int busReturn = userEeprom.getUInt8(addressStartupDelay - 1) & 0x2; // bit offset is 6: means 2^(7-bit offset)
    memset(channelConfig, 0, sizeof(channelConfig));
    inputs.begin(channels, currentVersion->baseAddress);

    Timeout startupDelay;
    // delay in config is in seconds
    unsigned int delay = userEeprom.getUInt16(addressStartupDelay) * 1000;
    startupDelay.start(delay);
    if (delay)
    {
        while (!startupDelay.expired())
        {
            inputs.scan();
            for (int unsigned i = 0; i < currentVersion->noOfChannels; i++)
            {
                unsigned int value;
                inputs.checkInput(i, &value);
            }
            waitForInterrupt();
        }
    }


    unsigned int busReturnLogic = userEeprom.getUInt8(addressStartupDelay - 1) & 0x01;

    for (unsigned int i = 0; i < MAX_LOGIC; i++)
    {
        if (userEeprom.getUInt8(currentVersion->logicBaseAddress + i * (11 + channels))
                != 0xff)
        {
            logicConfig[i] = new Logic(currentVersion->logicBaseAddress, i,
                    channels, busReturnLogic);
        }
    }

    inputs.scan();
    for (unsigned int i = 0; i < channels; i++)
    {
        unsigned int value;
        int configBase = currentVersion->baseAddress + 4 + i * 46;
        word channelType = userEeprom.getUInt16(configBase);
        Channel * channel;
        inputs.checkInput(i, &value);
        //leds.setStatus(i, value);
        for (unsigned int n = 0; n < MAX_LOGIC; n++)
        {
            if (logicConfig[n])
            {
                logicConfig[n]->inputChanged(n, value);
            }
        }

        busReturn = userEeprom.getUInt8(configBase + 32) || userEeprom.getUInt8(addressStartupDelay - 1) & 0x02; // param sendValue || readToggleObject
        switch (channelType)
        {
        case 0: // channel is configured as switch
            channel = new Switch(i, longKeyTime, configBase, busReturn, value);
            break;
        case 256: // channel is configured as switch short/long
            channel = new Switch2Level(i, longKeyTime, configBase, busReturn,
                    value);
            break;
        case 1: // channel is configured as dimmer
            channel = new Dimmer(i, longKeyTime, configBase, busReturn, value);
            break;
        case 2: // channel is configured as jalo
            channel = new Jalo(i, longKeyTime, configBase, busReturn, value);
            break;
        case 3: // channel is configured as scene
            channel = new Scene(i, longKeyTime, configBase, busReturn, value);
            break;
        case 4: // channel is configured as counter
            channel = new Counter(i, longKeyTime, configBase, busReturn, value);
            break;
        case 511: // channel is configured as LED output
        	channel = new LedOutput(i, longKeyTime, configBase, busReturn, value);
            break;
        default:
            channel = 0;
        }
        channelConfig[i] = channel;
    }

}