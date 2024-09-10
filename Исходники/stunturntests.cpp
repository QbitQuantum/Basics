// ---------------------------------------------------------------------------
// CStunTurnTests::TestOutgoingAddrL
// ---------------------------------------------------------------------------
//    
void CStunTurnTests::TestOutgoingAddrL()
    {
    TInetAddr inetAddr;
    TBuf<40> buffer;
    
    RDebug::Print( _L( "\nTEST CASE: Get outgoing address" ) );
    iWrapper->OutgoingAddr( inetAddr );
    
    inetAddr.Output( buffer );
    
    RDebug::Print( _L("TEST PRINT: CStunTurnTests::TestOutgoingAddrL, wrapper outgoing Address: %S:%d "), &buffer, inetAddr.Port() );
    if ( buffer.Length() == 0 )
        {
        User::Leave( KErrCompletion );
        }
    }