void WinMIDIStreamer::Reset(void)
{
    int                 i;

    midiStreamStop(midiStr);

    // Reset channel settings.
    for(i = 0; i <= 0xf; ++i) // All channels.
    {
        midiOutShortMsg((HMIDIOUT) midiStr, 0xe0 | i | 64 << 16); // Pitch bend.
    }

    midiOutReset((HMIDIOUT) midiStr);
}