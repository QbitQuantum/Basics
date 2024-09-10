bool MidiInRt::open(unsigned port)
{
    RtMidiIn *midiin = lazyInstance();
    m_midiin->closePort();
    m_errorSignaled = false;
    midiin->openPort(port, defaultPortName().toStdString());
    return !m_errorSignaled;
}