void MidiApple::closeDevices()
{
	m_inputSubs.clear();
	m_outputSubs.clear();

	QMapIterator<QString, MIDIEndpointRef> i( m_inputDevices );
	while( i.hasNext() )
	{
		midiInClose( i.next().value() );
	}
	
	QMapIterator<QString, MIDIEndpointRef> o( m_outputDevices );
	while( o.hasNext() )
	{
		midiInClose( o.next().value() );
	}
	
	m_inputDevices.clear();
	m_outputDevices.clear();
}