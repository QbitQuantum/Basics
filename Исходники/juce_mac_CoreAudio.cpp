    void updateDetailsFromDevice()
    {
        stopTimer();

        if (deviceID == 0)
            return;

        const ScopedLock sl (callbackLock);

        AudioObjectPropertyAddress pa;
        pa.mScope = kAudioObjectPropertyScopeWildcard;
        pa.mElement = kAudioObjectPropertyElementMaster;

        UInt32 isAlive;
        UInt32 size = sizeof (isAlive);
        pa.mSelector = kAudioDevicePropertyDeviceIsAlive;
        if (OK (AudioObjectGetPropertyData (deviceID, &pa, 0, 0, &size, &isAlive))
             && isAlive == 0)
            return;

        Float64 sr;
        size = sizeof (sr);
        pa.mSelector = kAudioDevicePropertyNominalSampleRate;
        if (OK (AudioObjectGetPropertyData (deviceID, &pa, 0, 0, &size, &sr)))
            sampleRate = sr;

        UInt32 framesPerBuf;
        size = sizeof (framesPerBuf);
        pa.mSelector = kAudioDevicePropertyBufferFrameSize;
        if (OK (AudioObjectGetPropertyData (deviceID, &pa, 0, 0, &size, &framesPerBuf)))
        {
            bufferSize = (int) framesPerBuf;
            allocateTempBuffers();
        }

        bufferSizes.clear();

        pa.mSelector = kAudioDevicePropertyBufferFrameSizeRange;

        if (OK (AudioObjectGetPropertyDataSize (deviceID, &pa, 0, 0, &size)))
        {
            HeapBlock <AudioValueRange> ranges;
            ranges.calloc (size, 1);

            if (OK (AudioObjectGetPropertyData (deviceID, &pa, 0, 0, &size, ranges)))
            {
                bufferSizes.add ((int) (ranges[0].mMinimum + 15) & ~15);

                for (int i = 32; i < 2048; i += 32)
                {
                    for (int j = size / (int) sizeof (AudioValueRange); --j >= 0;)
                    {
                        if (i >= ranges[j].mMinimum && i <= ranges[j].mMaximum)
                        {
                            bufferSizes.addIfNotAlreadyThere (i);
                            break;
                        }
                    }
                }

                if (bufferSize > 0)
                    bufferSizes.addIfNotAlreadyThere (bufferSize);
            }
        }

        if (bufferSizes.size() == 0 && bufferSize > 0)
            bufferSizes.add (bufferSize);

        sampleRates.clear();
        const double possibleRates[] = { 44100.0, 48000.0, 88200.0, 96000.0, 176400.0, 192000.0 };
        String rates;

        pa.mSelector = kAudioDevicePropertyAvailableNominalSampleRates;

        if (OK (AudioObjectGetPropertyDataSize (deviceID, &pa, 0, 0, &size)))
        {
            HeapBlock <AudioValueRange> ranges;
            ranges.calloc (size, 1);

            if (OK (AudioObjectGetPropertyData (deviceID, &pa, 0, 0, &size, ranges)))
            {
                for (int i = 0; i < numElementsInArray (possibleRates); ++i)
                {
                    bool ok = false;

                    for (int j = size / (int) sizeof (AudioValueRange); --j >= 0;)
                        if (possibleRates[i] >= ranges[j].mMinimum - 2 && possibleRates[i] <= ranges[j].mMaximum + 2)
                            ok = true;

                    if (ok)
                    {
                        sampleRates.add (possibleRates[i]);
                        rates << possibleRates[i] << ' ';
                    }
                }
            }
        }

        if (sampleRates.size() == 0 && sampleRate > 0)
        {
            sampleRates.add (sampleRate);
            rates << sampleRate;
        }

        JUCE_COREAUDIOLOG ("sr: " + rates);

        inputLatency = 0;
        outputLatency = 0;
        UInt32 lat;
        size = sizeof (lat);
        pa.mSelector = kAudioDevicePropertyLatency;
        pa.mScope = kAudioDevicePropertyScopeInput;
        if (AudioObjectGetPropertyData (deviceID, &pa, 0, 0, &size, &lat) == noErr)
            inputLatency = (int) lat;

        pa.mScope = kAudioDevicePropertyScopeOutput;
        size = sizeof (lat);

        if (AudioObjectGetPropertyData (deviceID, &pa, 0, 0, &size, &lat) == noErr)
            outputLatency = (int) lat;

        JUCE_COREAUDIOLOG ("lat: " + String (inputLatency) + " " + String (outputLatency));

        inChanNames.clear();
        outChanNames.clear();

        inputChannelInfo.calloc ((size_t) numInputChans + 2);
        numInputChannelInfos = 0;

        outputChannelInfo.calloc ((size_t) numOutputChans + 2);
        numOutputChannelInfos = 0;

        fillInChannelInfo (true);
        fillInChannelInfo (false);
    }