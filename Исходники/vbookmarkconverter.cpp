void CVBookmarkConverter::WriteL( const TDesC8 &aData )
    {
    if ( iBuffer )
        {
        TInt newPosition = iWriteBufPosition + aData.Length();

        if ( newPosition > iWriteBufSize )
            {
            TInt expandStep = newPosition - iWriteBufSize + 100;
            iBuffer->ExpandL( iWriteBufSize, expandStep );
            iWriteBufSize += expandStep;
            }

        iBuffer->Write( iWriteBufPosition, aData );
        iWriteBufPosition = newPosition;
        }
    else if( iDesc )
        {
        iDesc->Append( aData );       
        }
    }