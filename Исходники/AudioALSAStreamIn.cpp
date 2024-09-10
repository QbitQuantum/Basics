status_t AudioALSAStreamIn::setParameters(const String8 &keyValuePairs)
{
    ALOGD("+%s(): %s", __FUNCTION__, keyValuePairs.string());
    AudioParameter param = AudioParameter(keyValuePairs);

    /// keys
    const String8 keyInputSource = String8(AudioParameter::keyInputSource);
    const String8 keyRouting     = String8(AudioParameter::keyRouting);

    /// parse key value pairs
    status_t status = NO_ERROR;
    int value = 0;

    /// intput source
    if (param.getInt(keyInputSource, value) == NO_ERROR)
    {
        param.remove(keyInputSource);
        // TODO(Harvey): input source
        AudioAutoTimeoutLock _l(mLock);
        ALOGD("%s() InputSource = %d", __FUNCTION__, value);
        mStreamAttributeTarget.input_source = static_cast<audio_source_t>(value);

        if (mStreamAttributeTarget.BesRecord_Info.besrecord_ForceMagiASREnable == true)
        {
            ALOGD("%s() force input source to AUDIO_SOURCE_CUSTOMIZATION1", __FUNCTION__);
            mStreamAttributeTarget.input_source = AUDIO_SOURCE_CUSTOMIZATION1;
        }

        if (mStreamAttributeTarget.BesRecord_Info.besrecord_ForceAECRecEnable == true)
        {
            ALOGD("%s() force input source to AUDIO_SOURCE_CUSTOMIZATION2", __FUNCTION__);
            mStreamAttributeTarget.input_source = AUDIO_SOURCE_CUSTOMIZATION2;
        }
    }

    /// routing
    if (param.getInt(keyRouting, value) == NO_ERROR)
    {
        param.remove(keyRouting);

        AudioAutoTimeoutLock _l(mLock);

        audio_devices_t inputdevice = static_cast<audio_devices_t>(value);
        //only need to modify the device while VoIP
        if (mStreamAttributeTarget.BesRecord_Info.besrecord_voip_enable == true)
        {
            if (mStreamAttributeTarget.output_devices == AUDIO_DEVICE_OUT_SPEAKER)
            {
                if (inputdevice == AUDIO_DEVICE_IN_BUILTIN_MIC)
                {
                    if (USE_REFMIC_IN_LOUDSPK == 1)
                    {
                        inputdevice = AUDIO_DEVICE_IN_BACK_MIC;
                        ALOGD("%s() force change to back mic", __FUNCTION__);
                    }
                }
            }
        }
        status = mStreamManager->routingInputDevice(mStreamAttributeTarget.input_device, inputdevice);
    }

    if (param.size())
    {
        ALOGW("%s(), still have param.size() = %d, remain param = \"%s\"",
              __FUNCTION__, param.size(), param.toString().string());
        status = BAD_VALUE;
    }

    ALOGD("-%s(): %s ", __FUNCTION__, keyValuePairs.string());
    return status;
}