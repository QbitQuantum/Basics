    void run()
    {
        JNIEnv* env = getEnv();
        jshortArray audioBuffer = env->NewShortArray (actualBufferSize * jmax (numDeviceOutputChannels, numDeviceInputChannels));

        while (! threadShouldExit())
        {
            if (inputDevice != nullptr)
            {
                jint numRead = env->CallIntMethod (inputDevice, AudioRecord.read, audioBuffer, 0, actualBufferSize * numDeviceInputChannels);

                if (numRead < actualBufferSize * numDeviceInputChannels)
                {
                    DBG ("Audio read under-run! " << numRead);
                }

                jshort* const src = env->GetShortArrayElements (audioBuffer, 0);

                for (int chan = 0; chan < inputChannelBuffer.getNumChannels(); ++chan)
                {
                    AudioData::Pointer <AudioData::Float32, AudioData::NativeEndian, AudioData::NonInterleaved, AudioData::NonConst> d (inputChannelBuffer.getSampleData (chan));

                    if (chan < numDeviceInputChannels)
                    {
                        AudioData::Pointer <AudioData::Int16, AudioData::NativeEndian, AudioData::Interleaved, AudioData::Const> s (src + chan, numDeviceInputChannels);
                        d.convertSamples (s, actualBufferSize);
                    }
                    else
                    {
                        d.clearSamples (actualBufferSize);
                    }
                }

                env->ReleaseShortArrayElements (audioBuffer, src, 0);
            }

            if (threadShouldExit())
                break;

            {
                const ScopedLock sl (callbackLock);

                if (callback != nullptr)
                {
                    callback->audioDeviceIOCallback ((const float**) inputChannelBuffer.getArrayOfChannels(), numClientInputChannels,
                                                     outputChannelBuffer.getArrayOfChannels(), numClientOutputChannels,
                                                     actualBufferSize);
                }
                else
                {
                    outputChannelBuffer.clear();
                }
            }

            if (outputDevice != nullptr)
            {
                if (threadShouldExit())
                    break;

                jshort* const dest = env->GetShortArrayElements (audioBuffer, 0);

                for (int chan = 0; chan < numDeviceOutputChannels; ++chan)
                {
                    AudioData::Pointer <AudioData::Int16, AudioData::NativeEndian, AudioData::Interleaved, AudioData::NonConst> d (dest + chan, numDeviceOutputChannels);

                    const float* const sourceChanData = outputChannelBuffer.getSampleData (jmin (chan, outputChannelBuffer.getNumChannels() - 1));
                    AudioData::Pointer <AudioData::Float32, AudioData::NativeEndian, AudioData::NonInterleaved, AudioData::Const> s (sourceChanData);
                    d.convertSamples (s, actualBufferSize);
                }

                env->ReleaseShortArrayElements (audioBuffer, dest, 0);
                jint numWritten = env->CallIntMethod (outputDevice, AudioTrack.write, audioBuffer, 0, actualBufferSize * numDeviceOutputChannels);

                if (numWritten < actualBufferSize * numDeviceOutputChannels)
                {
                    DBG ("Audio write underrun! " << numWritten);
                }
            }
        }
    }