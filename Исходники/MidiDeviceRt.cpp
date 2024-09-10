bool CMidiDeviceRt::openMidiPort(midiType_t type, QString portName)
{
    unsigned int nPorts;
    QString name;
    RtMidi* midiDevice;


    if (portName.length() == 0)
        return false;

    int dev;
    if (type == MIDI_INPUT)
    {
        midiDevice = m_midiin;
        dev = 0;
    }
    else
    {
        midiDevice = m_midiout;
        dev = 1;
    }

    nPorts = midiDevice->getPortCount();

    for(unsigned int i=0; i< nPorts; i++)
    {
        // kotechnology creating indexed string from the post name
        name = addIndexToString(midiDevice->getPortName(i).c_str(),i);
        if (name == portName) // Test for a match
        {
            if (m_midiPorts[dev] >= 0)
                midiDevice->closePort();

            m_midiPorts[dev] = i;
            m_rawDataIndex = 0;

            midiDevice->openPort( i );
            return true;
        }
    }
    return false;
}