/// Routes the message to a remote or local destination
CMsg CMsgObjectInfo::Send( CMsg &x_rMsg )
{
    // Sanity check
    if ( !x_rMsg.IsValid() )
        return CMsg();

    // Can't be routed without an id
    if ( guid::CmpGuid( &IID_ZEROS, &x_rMsg.Mi().Dst()->GetId() ) )
        return CMsg();

    // Set our id in the return address
    x_rMsg.Mi().Src()->SetInstance( &m_guidId );

    // Is it for us?
    if ( guid::CmpGuid( &IID_ZEROS, &x_rMsg.Mi().Dst()->GetInstance() )
         || guid::CmpGuid( &m_guidId, &x_rMsg.Mi().Dst()->GetInstance() ) )
    {   
        // Short circuit the reply queue if needed
        if ( x_rMsg.Mi().WantReply() )
        {
            // Create reply signal
            x_rMsg.EnableReplyEvent( oexTRUE );

            // Set direct reply flag
            x_rMsg.SetDirectReply( oexTRUE );

        } // end if

        // Receive the message
        Recv( x_rMsg );
        
        return x_rMsg;

    } // end if

    // Send through the network
    return oexNet.Send( x_rMsg );
}