// -----------------------------------------------------------------------------
// 
// -----------------------------------------------------------------------------
//
TInt CPhoneRingingTone::CheckToneFileSize( const TDesC& aFile, 
                                           TInt aSizeLimitKB )
    {
    __LOGMETHODSTARTEND( EPhoneControl, "CPhoneRingingtone::CheckToneFileSize()" );
    //return KErrNone;
    
    // Get file size
    TInt size = 0;

    RFs fs;   
    TInt error = fs.Connect();
    TEntry entry;
    if ( KErrNone == error )
        {
        if (KErrNone == fs.Entry( aFile, entry ))
            {
            size = entry.iSize;
            }    
            
        // Check
        aSizeLimitKB *= Kkilo;
        if ( aSizeLimitKB  &&  size > aSizeLimitKB )
            {
            error = KErrTooBig;
            }
        }

    fs.Close();
    __PHONELOG1( 
        EBasic,
        EPhoneControl, 
        "CPhoneRingingtonePlayer::CheckToneFileSize - size (%d)",
        size );    
    return error;
   
    }