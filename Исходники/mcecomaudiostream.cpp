// -----------------------------------------------------------------------------
// CMceComAudioStream::UpdateL
// -----------------------------------------------------------------------------
//
void CMceComAudioStream::UpdateL( CMceComMediaStream& aStream )
    {  
    CMceComMediaStream::UpdateL( aStream );

    CMceComAudioStream* stream = static_cast<CMceComAudioStream*>( &aStream );
    
    RPointerArray<CMceComAudioCodec> updated;
    
    MceCleanupResetAndDestroyPushL( updated );

    for ( TInt i = 0 ; i < stream->CodecCount() ; ++i )
        {
        CMceComAudioCodec* update = stream->CodecL( i );
        TBool isUpdated = EFalse;
        TInt j = 0;

        while( !isUpdated && j < CodecCount() )
            {
            CMceComAudioCodec* codec = CodecL( j );
            if ( codec->Id() == update->Id() )
                {
                codec->UpdateL( *update );
                stream->RemoveCodecFromListL( i );
                delete update;
                updated.AppendL( codec );
                RemoveCodecFromListL( j );
                i--;
                isUpdated = ETrue;
                }
            j++;
            }
        }
        
    if ( CodecCount() > 0 )	//	Codecs have been removed
        {
        Session()->IsStructureChanged() = ETrue;
        }
        
    DestroyCodecs();
    
    while( updated.Count() > 0 )
        {
        AddCodecL( updated[0] );
        updated.Remove( 0 );
        }
        
    CleanupStack::PopAndDestroy();	// updated
            
    if ( stream->CodecCount() > 0 )	// Streams have been added
        {
        Session()->IsStructureChanged() = ETrue;
            
        while( stream->CodecCount() > 0 )
            {
            CMceComAudioCodec* add = stream->CodecL( 0 );
            AddCodecL( add );
            stream->RemoveCodecFromListL( 0 );
            }
        }
    }