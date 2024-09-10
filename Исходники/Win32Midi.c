void archMidiEnable(int enable)
{
    int i;

    midi.enabled = enable;
    if (midi.out.current[0] != NULL) {
        midiOutSetVolume((HMIDIOUT)midi.out.current[0]->handle, midi.out.volume * midi.enabled);
    }
    for (i = 0; i < 2; i++) {
        if (midi.in.current[i] != NULL) {
            if (enable && !midi.in.current[i]->recording) {
                midiInStart((HMIDIIN)midi.in.current[i]->handle);
                midi.in.current[i]->recording = 1;
            }
            else if (!enable && midi.in.current[i]->recording) {
                midiInStop((HMIDIIN)midi.in.current[i]->handle);
                midi.in.current[i]->recording = 0;
            }
        }
    }
}