// ---------------------------------------------------------------------------
// CSensrvDataHandler::GetData
// ---------------------------------------------------------------------------
//
TInt CSensrvDataHandler::GetData( TDes8& aDataPtr )
    {
    COMPONENT_TRACE( ( _L( "Sensrv Client - CSensrvDataHandler::GetData - Start" ) ) );
    TInt err( KErrNone );
    
    if( aDataPtr.Length() < iChannelInfo.iDataItemSize )
        {
        // aDataPtr is too small
        err = KErrOverflow;
        }
    else if( iGetDataCount >= iReadBufferCount || !iReadBuffer )
        {
        // data not found.
        err = KErrNotFound;
        }
    else
        {
        // set data
        TUint8* ptr = const_cast<TUint8*>( iReadBuffer->Des().Ptr() );
        ptr += ( iGetDataCount * iChannelInfo.iDataItemSize ); 
        
        aDataPtr.Copy( ptr, iChannelInfo.iDataItemSize );
        ++iGetDataCount;
        }
    
    COMPONENT_TRACE( ( _L( "Sensrv Client - CSensrvDataHandler::GetData - Return %d" ), err ) );
    return err;
    }