status_t A2dpAudioInterface::A2dpAudioStreamOut::setParameters(const String8& keyValuePairs)
{
    AudioParameter param = AudioParameter(keyValuePairs);
    String8 value;
    String8 key = String8("a2dp_sink_address");
    status_t status = NO_ERROR;
    int device;
    LOGV("A2dpAudioStreamOut::setParameters() %s", keyValuePairs.string());

    if (param.get(key, value) == NO_ERROR) {
        if (value.length() != strlen("00:00:00:00:00:00")) {
            status = BAD_VALUE;
        } else {
            setAddress(value.string());
        }
        param.remove(key);
    }
    key = String8("closing");
    if (param.get(key, value) == NO_ERROR) {
        mClosing = (value == "true");
        param.remove(key);
    }
    key = AudioParameter::keyRouting;
    if (param.getInt(key, device) == NO_ERROR) {
        if (AudioSystem::isA2dpDevice((AudioSystem::audio_devices)device)) {
            mDevice = device;
            status = NO_ERROR;
        } else {
            status = BAD_VALUE;
        }
        param.remove(key);
    }

    if (param.size()) {
        status = BAD_VALUE;
    }
    return status;
}