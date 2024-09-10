void Win32MidiOutputDevice::writeSysEx(QByteArray message)
{
    if(message.isEmpty())
        return;

    if (isOpen() == false)
        return;

    MIDIHDR midiHdr;

    /* Store pointer in MIDIHDR */
    midiHdr.lpData = (LPSTR)message.data();

    /* Store its size in the MIDIHDR */
    midiHdr.dwBufferLength = message.count();

    /* Flags must be set to 0 */
    midiHdr.dwFlags = 0;

    UINT err;
    /* Prepare the buffer and MIDIHDR */
    err = midiOutPrepareHeader(m_handle,  &midiHdr, sizeof(MIDIHDR));
    if (!err)
    {
        /* Output the SysEx message */
        err = midiOutLongMsg(m_handle, &midiHdr, sizeof(MIDIHDR));
        if (err)
            qDebug() << "Error while sending SysEx message";

        /* Unprepare the buffer and MIDIHDR */
        while (MIDIERR_STILLPLAYING == midiOutUnprepareHeader(m_handle, &midiHdr, sizeof(MIDIHDR)))
        {
            /* Should put a delay in here rather than a busy-wait */
        }
    }

    /* Close the MIDI device */
    midiOutClose(m_handle);
}