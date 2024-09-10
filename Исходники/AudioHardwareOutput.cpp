status_t AudioHardwareOutput::setParameters(const char* kvpairs) {
    AudioParameter param = AudioParameter(String8(kvpairs));
    status_t status = NO_ERROR;
    float floatVal;
    int intVal;
    Settings initial, s;

    {
        // Record the initial state of the settings from inside the lock.  Then
        // leave the lock in order to parse the changes to be made.
        Mutex::Autolock _l(mSettingsLock);
        initial = s = mSettings;
    }

    /***************************************************************
     *                     HDMI Audio Options                      *
     ***************************************************************/
    if (param.getInt(kHDMIAllowedParamKey, intVal) == NO_ERROR) {
        s.hdmi.allowed = (intVal != 0);
        param.remove(kHDMIAllowedParamKey);
    }

    if ((param.getFloat(kHDMIDelayCompParamKey, floatVal) == NO_ERROR) &&
        (floatVal >= 0.0) &&
        (floatVal <= AudioOutput::kMaxDelayCompensationMSec)) {
        uint32_t delay_comp = static_cast<uint32_t>(floatVal * 1000.0);
        s.hdmi.delayCompUsec = delay_comp;
        param.remove(kHDMIDelayCompParamKey);
    }

    if (param.getInt(kFixedHDMIOutputParamKey, intVal) == NO_ERROR) {
        s.hdmi.isFixed = (intVal != 0);
        param.remove(kFixedHDMIOutputParamKey);
    }

    if ((param.getFloat(kFixedHDMIOutputLevelParamKey, floatVal) == NO_ERROR)
        && (floatVal <= 0.0)) {
        s.hdmi.fixedLvl = floatVal;
        param.remove(kFixedHDMIOutputLevelParamKey);
    }

    /***************************************************************
     *                       Other Options                         *
     ***************************************************************/
    if ((param.getFloat(kVideoDelayCompParamKey, floatVal) == NO_ERROR) &&
        (floatVal >= 0.0) &&
        (floatVal <= AudioOutput::kMaxDelayCompensationMSec)) {
        s.videoDelayCompUsec = static_cast<uint32_t>(floatVal * 1000.0);
        param.remove(kVideoDelayCompParamKey);
    }

    if (param.size())
        status = BAD_VALUE;

    // If there was a change made to settings, go ahead and apply it now.
    bool allowedOutputsChanged = false;
    if (memcmp(&initial, &s, sizeof(initial)))  {
        Mutex::Autolock _l1(mOutputLock);
        Mutex::Autolock _l2(mSettingsLock);

        if (memcmp(&initial.hdmi, &s.hdmi, sizeof(initial.hdmi)))
            allowedOutputsChanged = allowedOutputsChanged ||
                applyOutputSettings_l(initial.hdmi, s.hdmi, mSettings.hdmi,
                                      HDMIAudioOutput::classDevMask());

        if (initial.videoDelayCompUsec != s.videoDelayCompUsec)
            mSettings.videoDelayCompUsec = s.videoDelayCompUsec;

        uint32_t tmp = 0;
        if (mSettings.hdmi.allowed && (tmp < mSettings.hdmi.delayCompUsec))
            tmp = mSettings.hdmi.delayCompUsec;
        if (mMaxDelayCompUsec != tmp)
            mMaxDelayCompUsec = tmp;
    }

    if (allowedOutputsChanged) {
        Mutex::Autolock _l(mStreamLock);
        updateTgtDevices_l();
    }

    return status;
}