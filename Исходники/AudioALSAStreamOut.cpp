status_t AudioALSAStreamOut::setParameters(const String8 &keyValuePairs)
{
    ALOGD("+%s(): %s", __FUNCTION__, keyValuePairs.string());
    AudioParameter param = AudioParameter(keyValuePairs);

    /// keys
    const String8 keyRouting = String8(AudioParameter::keyRouting);
    const String8 keySampleRate = String8(AudioParameter::keySamplingRate);
    const String8 keyDynamicSampleRate = String8("DynamicSampleRate");
    const String8 keyLowLatencyMode = String8("LowLatencyMode");
    const String8 keyRoutingToNone = String8(AudioParameter::keyRoutingToNone);
    const String8 keyFmDirectControl = String8(AudioParameter::keyFmDirectControl);

    audio_devices_t mydevice = 0;


    /// parse key value pairs
    status_t status = NO_ERROR;
    int value = 0;

    /// routing
    if (param.getInt(keyRouting, value) == NO_ERROR)
    {
        param.remove(keyRouting);

        mydevice = static_cast<audio_devices_t>(value);
        ALOGD("%s(), mydevice 0x%x", __FUNCTION__, mydevice);

        AudioAutoTimeoutLock _l(mLock);
        if (mStreamOutType == STREAM_OUT_PRIMARY)
        {
            status = mStreamManager->routingOutputDevice(mStreamAttributeSource.output_devices, static_cast<audio_devices_t>(value));
        }
        else if ((mStreamOutType == STREAM_OUT_HDMI_STEREO) || (mStreamOutType == STREAM_OUT_HDMI_MULTI_CHANNEL))
        {
            ALOGD("%s(), HDMI  \"%s\"", __FUNCTION__, param.toString().string());
            status = mStreamManager->routingOutputDevice(mStreamAttributeSource.output_devices, static_cast<audio_devices_t>(value));
        }
        else
        {
            ALOGW("%s(), NUM_STREAM_OUT_TYPE \"%s\"", __FUNCTION__, param.toString().string());
            status = INVALID_OPERATION;
        }
    }
    if (param.getInt(keyFmDirectControl, value) == NO_ERROR)
    {
        param.remove(keyFmDirectControl);

        AudioAutoTimeoutLock _l(mLock);
        AudioALSAFMController::getInstance()->setUseFmDirectConnectionMode(value?true:false);

    }
    // routing none, for no stream but has device change. e.g. vow path change
    if (param.getInt(keyRoutingToNone, value) == NO_ERROR)
    {
        param.remove(keyRoutingToNone);

        AudioAutoTimeoutLock _l(mLock);
        status = mStreamManager->DeviceNoneUpdate();

    }
    // samplerate
    if (param.getInt(keySampleRate, value) == NO_ERROR)
    {
        param.remove(keySampleRate);
        AudioAutoTimeoutLock _l(mLock);
        if (mPlaybackHandler == NULL)
        {
            UpdateSampleRate(value);
        }
        else
        {
            status = INVALID_OPERATION;
        }
    }

    /// sample rate
    if (param.getInt(keyDynamicSampleRate, value) == NO_ERROR)
    {
        param.remove(keyRouting);

        AudioAutoTimeoutLock _l(mLock);
        if (mStreamOutType == STREAM_OUT_PRIMARY)
        {
            status = NO_ERROR; //AudioALSASampleRateController::getInstance()->setPrimaryStreamOutSampleRate(value); // TODO(Harvey): enable it later
        }
        else
        {
            ALOGW("%s(), HDMI bypass \"%s\"", __FUNCTION__, param.toString().string());
            status = INVALID_OPERATION;
        }
    }

#ifdef MTK_DYNAMIC_CHANGE_HAL_BUFFER_SIZE
    // set low latency
    if (param.getInt(keyLowLatencyMode, value) == NO_ERROR)
    {
        param.remove(keyLowLatencyMode);
        setLowLatencyMode(value);
    }
#endif

    if (param.size())
    {
        ALOGW("%s(), still have param.size() = %d, remain param = \"%s\"",
              __FUNCTION__, param.size(), param.toString().string());
        status = BAD_VALUE;
    }

    ALOGD("-%s(): %s ", __FUNCTION__, keyValuePairs.string());
    return status;
}