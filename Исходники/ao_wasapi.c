static int control(struct ao *ao, enum aocontrol cmd, void *arg)
{
    struct wasapi_state *state = (struct wasapi_state *)ao->priv;
    ao_control_vol_t *vol = (ao_control_vol_t *)arg;
    BOOL mute;

    switch (cmd) {
    case AOCONTROL_GET_VOLUME:
        if (state->opt_exclusive)
            IAudioEndpointVolume_GetMasterVolumeLevelScalar(state->pEndpointVolumeProxy,
                                                            &state->audio_volume);
        else
            ISimpleAudioVolume_GetMasterVolume(state->pAudioVolumeProxy,
                                               &state->audio_volume);

        /* check to see if user manually changed volume through mixer;
           this information is used in exclusive mode for restoring the mixer volume on uninit */
        if (state->audio_volume != state->previous_volume) {
            MP_VERBOSE(state, "mixer difference: %.2g now, expected %.2g\n",
                       state->audio_volume, state->previous_volume);
            state->initial_volume = state->audio_volume;
        }

        vol->left = vol->right = 100.0f * state->audio_volume;
        return CONTROL_OK;
    case AOCONTROL_SET_VOLUME:
        state->audio_volume = vol->left / 100.f;
        if (state->opt_exclusive)
            IAudioEndpointVolume_SetMasterVolumeLevelScalar(state->pEndpointVolumeProxy,
                                                            state->audio_volume, NULL);
        else
            ISimpleAudioVolume_SetMasterVolume(state->pAudioVolumeProxy,
                                               state->audio_volume, NULL);

        state->previous_volume = state->audio_volume;
        return CONTROL_OK;
    case AOCONTROL_GET_MUTE:
        if (state->opt_exclusive)
            IAudioEndpointVolume_GetMute(state->pEndpointVolumeProxy, &mute);
        else
            ISimpleAudioVolume_GetMute(state->pAudioVolumeProxy, &mute);
        *(bool*)arg = mute;

        return CONTROL_OK;
    case AOCONTROL_SET_MUTE:
        mute = *(bool*)arg;
        if (state->opt_exclusive)
            IAudioEndpointVolume_SetMute(state->pEndpointVolumeProxy, mute, NULL);
        else
            ISimpleAudioVolume_SetMute(state->pAudioVolumeProxy, mute, NULL);

        return CONTROL_OK;
    case AOCONTROL_HAS_PER_APP_VOLUME:
        return CONTROL_TRUE;
    case AOCONTROL_UPDATE_STREAM_TITLE: {
        MP_VERBOSE(state, "Updating stream title to \"%s\"\n", (char*)arg);
        wchar_t *title = mp_from_utf8(NULL, (char*)arg);

        wchar_t *tmp = NULL;

        /* There is a weird race condition in the IAudioSessionControl itself --
           it seems that *sometimes* the SetDisplayName does not take effect and it still shows
           the old title. Use this loop to insist until it works. */
        do {
            IAudioSessionControl_SetDisplayName(state->pSessionControlProxy, title, NULL);

            SAFE_RELEASE(tmp, CoTaskMemFree(tmp));
            IAudioSessionControl_GetDisplayName(state->pSessionControlProxy, &tmp);
        } while (lstrcmpW(title, tmp));
        SAFE_RELEASE(tmp, CoTaskMemFree(tmp));
        talloc_free(title);

        return CONTROL_OK;
    }
    default:
        return CONTROL_UNKNOWN;
    }
}