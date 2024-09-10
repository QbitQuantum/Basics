static void winwave_fini_in (HWVoiceIn *hw)
{
    int i;
    MMRESULT mr;
    WaveVoiceIn *wave = (WaveVoiceIn *) hw;

    mr = waveInReset (wave->hwi);
    if (mr != MMSYSERR_NOERROR) {
        winwave_logerr (mr, "waveInReset");
    }

    for (i = 0; i < conf.adc_headers; ++i) {
        mr = waveInUnprepareHeader (wave->hwi, &wave->hdrs[i],
                                     sizeof (wave->hdrs[i]));
        if (mr != MMSYSERR_NOERROR) {
            winwave_logerr (mr, "waveInUnprepareHeader(%d)", i);
        }
    }

    winwave_anal_close_in (wave);

    if (wave->event) {
        qemu_del_wait_object (wave->event, winwave_poll, wave);
        if (!CloseHandle (wave->event)) {
            dolog ("ADC CloseHandle failed %lx\n", GetLastError ());
        }
        wave->event = NULL;
    }

    g_free (wave->pcm_buf);
    wave->pcm_buf = NULL;

    g_free (wave->hdrs);
    wave->hdrs = NULL;
}