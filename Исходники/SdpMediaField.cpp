// ---------------------------------------------------------------------------
// CSdpMediaField::KeepFormatL
// ---------------------------------------------------------------------------
//
EXPORT_C void CSdpMediaField::KeepFormatL(const TDesC8& aFormat)
{
    if ( !iFormatList )
    {
        User::Leave( KErrSdpCodecMediaField );
    }
    // Empty set will continue to be empty
    if ( iFormatList->Des().Length() > 0 )
    {
        HBufC8* formatList = aFormat.AllocLC();
        // Mark all format attributes not aFormat so that they will be deleted
        RArray<TInt> removedObjs;
        CleanupClosePushL( removedObjs );
        for ( TInt i( 0 ); i < iFmtAttrFields->Count(); i++ )
        {
            if (aFormat.CompareF((*iFmtAttrFields)[i]->Format()) != 0)
            {
                User::LeaveIfError( removedObjs.Append( i ) );
            }
        }
        // Delete attribute fields
        TInt removedCount( 0 );
        while ( removedObjs.Count() > 0 )
        {
            CSdpFmtAttributeField* obj =
                (*iFmtAttrFields)[removedObjs[0] - removedCount];
            delete obj;
            iFmtAttrFields->Remove( removedObjs[0] - removedCount );
            removedObjs.Remove( 0 );
            removedCount++;
        }
        CleanupStack::PopAndDestroy();  // removedObjs
        // Change format list
        delete iFormatList;
        iFormatList = formatList;
        CleanupStack::Pop();    // formatList
    }
}