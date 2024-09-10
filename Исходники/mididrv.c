/* closes the MIDI-In device*/
void mididrv_in_close(void)
{
    MMRESULT ret;
#ifdef DEBUG
    log_message(mididrv_log, "in_close");
#endif
    if (!handle_in) {
        log_error(mididrv_log, "Attempt to close MIDI-In device that wasn't open!");
        return;
    }
    /* can theoretically return MMSYSERR_INVALHANDLE */
    ret = midiInReset(handle_in);

    ret = midiInClose(handle_in);
    if (ret != MMSYSERR_NOERROR) {
        log_error(mididrv_log, "Couldn't close MIDI-In device.");
    }
    handle_in = 0;
}