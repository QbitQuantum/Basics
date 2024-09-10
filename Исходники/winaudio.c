static void
winaudio_in_fini (HWVoiceIn *hw)
{
    WinAudioIn*  s = (WinAudioIn*) hw;
    int           i;

    if (s->wavein) {
        waveInReset(s->wavein);
            s->wavein = 0;
    }

    for ( i=0; i<NUM_OUT_BUFFERS; ++i ) {
        if ( s->buffers[i].dwUser != 0xFFFF ) {
            waveInUnprepareHeader(
                s->wavein, &s->buffers[i], sizeof(s->buffers[i]) );
                s->buffers[i].dwUser = 0xFFFF;
        }
    }

    if (s->buffer_bytes != NULL) {
        qemu_free(s->buffer_bytes);
        s->buffer_bytes = NULL;
    }

    if (s->wavein) {
        waveInClose(s->wavein);
        s->wavein = NULL;
    }
}