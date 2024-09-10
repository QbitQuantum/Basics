void HDMIAudioCaps::getChannelMasksForAF(String8& masks) {
    Mutex::Autolock _l(mLock);
    masks.clear();

    // If the sink does not support basic audio, then it supports no audio.
    if (!mBasicAudioSupported)
        return;

    masks.append("AUDIO_CHANNEL_OUT_STEREO");

    // To keep things simple, only report mode information for the mode
    // which supports the maximum number of channels.
    ssize_t ndx = getMaxChModeNdx_l();
    if (ndx < 0)
        return;

    if (mModes[ndx].max_ch >= 6) {
        if (masks.length())
            masks.append("|");

        masks.append((mModes[ndx].max_ch >= 8)
                ? "AUDIO_CHANNEL_OUT_5POINT1|AUDIO_CHANNEL_OUT_7POINT1"
                : "AUDIO_CHANNEL_OUT_5POINT1");
    }
}