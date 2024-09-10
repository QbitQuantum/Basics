void SerialConnection::SendNMEAMessage( wxString &message, wxString &source )
{
    if ( !IsOpen() )
        return;
    if ( FilterOutput( message, source ) )
    {
        wxCharBuffer buffer = message.ToAscii();
        WriteDevice( buffer.data(), strlen( buffer.data() ) );
        buffer = m_EOS.ToAscii();
        WriteDevice( buffer.data(), strlen( buffer.data() ) );
    }
}