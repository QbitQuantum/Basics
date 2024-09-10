void UT_CDTMFPayloadFormatRead::UT_CDTMFPayloadFormatRead_HandleDTMFTones()
    {
    TDTMFEventPayloadInfo payloadinfo;
 
    payloadinfo.SetEvent( '7' );
    payloadinfo.SetEndBit( 1 );
    payloadinfo.SetVolume( 4 );
    payloadinfo.SetDuration( 400 );
    
    iRead->HandleDTMFTones();
    
    User::LeaveIfError( iRead->iEventPayloadInfo.Append( payloadinfo ) );
    iRead->HandleDTMFTones();
    }