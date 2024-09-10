// KErrBadDescriptor, if message length too small
// KErrUnderFlow, if message length too big.
// KErrCouldNotConnect, if receiver object is out of scope.
TInt DISICLTransceiver::ValidateISIMessage(
        TDes8& aMessage
        )
    {

    C_TRACE( ( _T( "DISICLTransceiver::ValidateISIMessage 0x%x>" ), &aMessage ) );
    const TUint16 descLength( aMessage.Length() );
    TInt msgOk( KErrNone );
    msgOk = ( ISI_HEADER_OFFSET_MESSAGEID >= descLength ) ? KErrBadDescriptor : msgOk;
    TRACE_ASSERT_INFO( msgOk == KErrNone, msgOk );
    // Get ISI message length after known that the descriptor is big enough.
    const TUint8* msgPtr( aMessage.Ptr() );
    const TUint16 isiMsgLength( GET_LENGTH( msgPtr ) + PN_HEADER_SIZE );
    // If the descriptor length is less than ISI message length.
    msgOk = ( ( msgOk == KErrNone && isiMsgLength > descLength ) ? KErrUnderflow : msgOk );
    TRACE_ASSERT_INFO( msgOk == KErrNone, msgOk );
    // If the ISI message length is bigger that the largest supported.
    msgOk = ( ( msgOk == KErrNone && isiMsgLength > KMaxISIMsgSize ) ? KErrUnderflow : msgOk );
    TRACE_ASSERT_INFO( msgOk == KErrNone, msgOk );
    // If the ISI message length with PN_HEADER_SIZE is less or equal than ISI_HEADER_OFFSET_MESSAGEID.
    msgOk = ( ( msgOk == KErrNone && isiMsgLength <= ISI_HEADER_OFFSET_MESSAGEID ) ? KErrUnderflow : msgOk );
    TRACE_ASSERT_INFO( msgOk == KErrNone, msgOk );
    TRACE_ASSERT_INFO( msgOk == KErrNone, isiMsgLength );
    TRACE_ASSERT_INFO( msgOk == KErrNone, descLength );
    C_TRACE( ( _T( "DISICLTransceiver::ValidateISIMessage %d<" ), msgOk ) );
    return msgOk;
    }