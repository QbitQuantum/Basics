status_t AudioStreamInMotorola::setParameters(const String8& keyValuePairs)
{
    AudioParameter param = AudioParameter(keyValuePairs);
    status_t status = NO_ERROR;
    int device;
    String8 key;
    int source;
    LOGD("setParameters(%s) called", keyValuePairs.string());

    // reading routing parameter
    key = String8(AudioParameter::keyRouting);
    if (param.getInt(key, device) == NO_ERROR) {
        LOGD("setParameters(): set input routing %x", device);
        if (device & (device - 1)) {
            LOGE("setParameters(): device value is invalid for routing");
            status = BAD_VALUE;
        } else {
            mDevices = device;
            status = mHardware->doRouting();
        }
        param.remove(key);
    }

    if (param.size()) {
        LOGE("setParameters(): parameter size is invalid");
        status = BAD_VALUE;
    }

    return status;
}