void JackWinMMEDriver::CloseInput(MidiSlot* slot)
{
    MMRESULT res;
    int retry = 0;

    if (slot->fHandle == 0)
        return;

    HMIDIIN handle = (HMIDIIN)slot->fHandle;
    slot->fHeader->dwUser = 0;
    res = midiInStop(handle);
    if (res != MMSYSERR_NOERROR) {
        jack_error("midiInStop error");
    }
    res = midiInReset(handle);
    if (res != MMSYSERR_NOERROR) {
        jack_error("midiInReset error");
    }
    res = midiInUnprepareHeader(handle, slot->fHeader, sizeof(MIDIHDR));
    if (res != MMSYSERR_NOERROR) {
        jack_error("midiInUnprepareHeader error");
    }
    do {
        res = midiInClose(handle);
        if (res != MMSYSERR_NOERROR) {
            jack_error("midiInClose error");
        }
        if (res == MIDIERR_STILLPLAYING)
            midiInReset(handle);
        Sleep (10);
        retry++;
    } while ((res == MIDIERR_STILLPLAYING) && (retry < 10));

    if (slot->fHeader) {
        GlobalFreePtr(slot->fHeader);
    }
}