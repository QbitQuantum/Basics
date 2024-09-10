t_CKBOOL MidiOutManager::open( MidiOut * mout, t_CKINT device_num )
{
    // see if port not already open
    if( device_num >= (t_CKINT)the_mouts.capacity() || !the_mouts[device_num] )
    {
        // allocate
        RtMidiOut * rtmout = new RtMidiOut;
        try {
            rtmout->openPort( device_num );
        } catch( RtError & err ) {
            if( !mout->m_suppress_output )
            {
                // print it
                EM_error2( 0, "MidiOut: couldn't open MIDI port %i...", device_num );
                err.getMessage();
                // const char * e = err.getMessage().c_str();
                // EM_error2( 0, "...(%s)", err.getMessage().c_str() );
            }
            return FALSE;
        }

        // resize?
        if( device_num >= (t_CKINT)the_mouts.capacity() )
        {
            t_CKINT size = the_mouts.capacity() * 2;
            if( device_num >= size ) size = device_num + 1;
            the_mouts.resize( size );
        }

        // put rtmout in vector for future generations
        the_mouts[device_num] = rtmout;
    }

    // found (always) (except when it doesn't get here)
    mout->mout = the_mouts[device_num];
    mout->m_device_num = (t_CKUINT)device_num;

    // done
    return TRUE;
}