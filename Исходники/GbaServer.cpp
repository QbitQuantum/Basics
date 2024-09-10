// -----------------------------------------------------------------------------
// CGbaServer::WriteOptionL()
// -----------------------------------------------------------------------------
//
void CGbaServer::WriteOptionL(const TUid& aOptionID, const TDesC8& aValue) const
{
    GBA_TRACE_DEBUG(("WriteOptionL"));
    TInt pushCount = 0;
    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL( fs );
    pushCount++;
    TFindFile folder( fs );

    TFileName fullPath;
    MakePrivateFilenameL(fs, KGbaIniFileName, fullPath);
    EnsurePathL(fs, fullPath );

    GBA_TRACE_DEBUG(fullPath);

    TInt err = folder.FindByDir( fullPath, KNullDesC);

    if (  err == KErrNotFound || err == KErrNone )
    {
        CDictionaryFileStore* pStore = CDictionaryFileStore::OpenLC( fs, fullPath, KGbaIniUid );
        pushCount++;

        RDictionaryWriteStream wrs;
        CleanupClosePushL( wrs );
        wrs.AssignL(*pStore,aOptionID);

        wrs.WriteInt32L(aValue.Length());
        wrs.WriteL(aValue);
        wrs.CommitL();

        pStore->CommitL();
        CleanupStack::PopAndDestroy( &wrs );
        CleanupStack::PopAndDestroy( pushCount );
        GBA_TRACE_DEBUG(aValue);
    }
    else
    {
        CleanupStack::PopAndDestroy( pushCount );
        User::LeaveIfError( err );
    }
}