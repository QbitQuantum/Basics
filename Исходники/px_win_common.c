int open_mixers(px_mixer *Px, UINT deviceIn, UINT deviceOut)
{
    PxInfo*info;
    MMRESULT res;
    OSVERSIONINFO verInfo;

    memset(&verInfo, 0, sizeof(verInfo));
    verInfo.dwOSVersionInfoSize = sizeof(verInfo);
    GetVersionEx(&verInfo);
    if (verInfo.dwMajorVersion >= 6) {
        return open_ep_mixers(Px, deviceIn, deviceOut);
    }

    res = mixerGetID((HMIXEROBJ) (deviceIn == WAVE_MAPPER ? 0 : deviceIn),
                     &deviceIn,
                     MIXER_OBJECTF_WAVEIN);
    if (res != MMSYSERR_NOERROR) {
        return FALSE;
    }

    res = mixerGetID((HMIXEROBJ) (deviceOut == WAVE_MAPPER ? 0 : deviceOut),
                     &deviceOut,
                     MIXER_OBJECTF_WAVEIN);
    if (res != MMSYSERR_NOERROR) {
        return FALSE;
    }

    if (!initialize(Px)) {
        return FALSE;
    }

    info = (PxInfo *) Px->info;
    info->hInputMixer = NULL;
    info->hOutputMixer = NULL;
    info->numInputs = 0;
    info->muxID = 0;
    info->speakerID = 0;
    info->waveID = 0;

    if (deviceIn != UINT_MAX) {
        res = mixerOpen((LPHMIXER) &info->hInputMixer,
                        deviceIn,
                        0,
                        0,
                        MIXER_OBJECTF_MIXER);
        if (res != MMSYSERR_NOERROR) {
            return cleanup(Px);
        }

        info->muxID = find_ctrl(info->hInputMixer,
                                MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
                                MIXERCONTROL_CONTROLTYPE_MUX);
        if (info->muxID == -1) {
            info->muxID = find_ctrl(info->hInputMixer,
                                    MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
                                    MIXERCONTROL_CONTROLTYPE_MIXER);
        }

        info->numInputs = get_ctrls(info->hInputMixer,
                                    MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
                                    &info->src);

        if (info->numInputs == 0) {
            return cleanup(Px);
        }
    }

    if (deviceOut != UINT_MAX) {
        res = mixerOpen((LPHMIXER) &info->hOutputMixer,
                        deviceOut,
                        0,
                        0,
                        MIXER_OBJECTF_MIXER);
        if (res != MMSYSERR_NOERROR) {
            return cleanup(Px);
        }

        info->speakerID = find_ctrl(info->hOutputMixer,
                                    MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
                                    MIXERCONTROL_CONTROLTYPE_VOLUME);

        info->waveID = find_ctrl(info->hOutputMixer,
                                 MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT,
                                 MIXERCONTROL_CONTROLTYPE_VOLUME);

        info->numOutputs = get_ctrls(info->hOutputMixer,
                                     MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
                                     &info->dst);

        if (info->numOutputs == 0) {
            return cleanup(Px);
        }
    }

    return TRUE;
}