void rtmidi_close_port (RtMidiPtr device)
{
#if defined(__NO_EXCEPTIONS__)
    RtMidi* rtm = (RtMidi*) device->ptr;
    rtm->resetError();
    rtm->closePort ();
    if (rtm->isError()) {
        device->ok  = false;
        device->msg = rtm->getError().what ();
    }
#else
    try { 
        ((RtMidi*) device->ptr)->closePort ();

    } catch (const RtMidiError & err) {
        device->ok  = false;
        device->msg = err.what ();
    }
#endif
}