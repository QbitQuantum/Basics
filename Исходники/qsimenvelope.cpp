/*!
    Returns an envelope object corresponding to the data in \a pdu.
    The data is decoded as described in 3GPP TS 11.14.

    \sa toPdu()
*/
QSimEnvelope QSimEnvelope::fromPdu( const QByteArray& pdu )
{
    QSimEnvelope env;
    QByteArray content;
    uint posn = 0;
    uint newPosn;
    uint tag, length;
    readBer( pdu, posn, tag, length );
    if ( ( tag & 0xF0 ) != 0xD0 ) {
        // Doesn't appear to be a valid ENVELOPE.
        return env;
    }
    env.setType( (QSimEnvelope::Type)tag );
    content = pdu.mid( posn, length );
    posn = 0;
    readBer( content, posn, tag, length );
    for (;;) {
        if ( ( posn + length ) > (uint)content.size() )
            break;
        newPosn = posn + length;
        switch ( tag & 0x7F ) {

            case 0x02:
            {
                // Device identities, GSM 11.14, section 12.7.
                if ( length >= 2 ) {
                    env.setSourceDevice
                        ( (QSimCommand::Device)( content[posn] & 0xFF ) );
                    env.setDestinationDevice
                        ( (QSimCommand::Device)( content[posn + 1] & 0xFF ) );
                }
            }
            break;

            case 0x10:
            {
                // Menu item identifier, GSM 11.14, section 12.10.
                if ( length > 0 )
                    env.setMenuItem( (uint)(content[posn] & 0xFF) );
            }
            break;

            case 0x15:
            {
                // Help requested, GSM 11.14, section 12.21.
                env.setRequestHelp( true );
            }
            break;

            case 0x19:
            {
                // Event list, GSM 11.14, section 12.25.
                if ( length > 0 )
                    env.setEvent( (QSimEnvelope::Event)( content[posn] & 0xFF ) );
            }
            break;

            default:
            {
                // Don't know what this is, so add it as an extension field.
                env.addExtensionField( tag, content.mid( posn, length ) );
            }
            break;
        }
        posn = newPosn;
        if ( posn >= (uint)content.size() )
            break;
        readBer( content, posn, tag, length );
    }
    return env;
}