// ---------------------------------------------------------------------------
// Write the file to correct directory.
// ---------------------------------------------------------------------------
//
EXPORT_C void CXIMPTestFileTool::PluginStoreL( const TDesC8& aExternalizedObject )
    {
    HBufC* fileName = GetFileNameLC( 
            KFileToolPluginDirBase,
            iObjIndex );

    RFileWriteStream out;
    CleanupClosePushL( out );
    out.Create( iFs, *fileName, EFileWrite|EFileStream|EFileShareAny );

    // write the file
    TUint32 len = aExternalizedObject.Length();
    out.WriteUint32L( len );
    out.WriteL( aExternalizedObject );
    CleanupStack::PopAndDestroy(); // out

    CleanupStack::PopAndDestroy( fileName ); // fileName

    // next file will have a new index
    iObjIndex++;
    }