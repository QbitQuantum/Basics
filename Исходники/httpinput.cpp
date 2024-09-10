void
HttpInput::setState( RadioState newState )
{
    // These are the only valid states
    Q_ASSERT( newState == State_FetchingStream ||
              newState == State_StreamFetched ||
              newState == State_Buffering ||
              newState == State_Streaming ||
              newState == State_Stopped );

    if ( newState != m_state )
    {
        LOGL( 4, "HttpInput state: " << radioState2String( newState ) );

        m_state = newState;

        emit stateChanged( newState );
    }
}