// ---------------------------------------------------------------------------
// CFotaDB::StateToRowL
// Converts state object to database row (into view object)
// ---------------------------------------------------------------------------
void CFotaDB::StateToRowL(const TPackageState& aPkg, const TDesC8& aPkgURL,
        RDbView& aView)
    {
    HBufC* pkgname = HBufC::NewLC(aPkg.iPkgName.Length());
    HBufC* version = HBufC::NewLC(aPkg.iPkgVersion.Length());

    pkgname->Des().Copy(aPkg.iPkgName);
    version->Des().Copy(aPkg.iPkgVersion);

    aView.SetColL(iColSet->ColNo(KColPkgId), aPkg.iPkgId);
    aView.SetColL(iColSet->ColNo(KColResult), aPkg.iResult);
    aView.SetColL(iColSet->ColNo(KColState), aPkg.iState);
    aView.SetColL(iColSet->ColNo(KColProfileId), aPkg.iProfileId);
    aView.SetColL(iColSet->ColNo(KColPkgName), *pkgname);
    aView.SetColL(iColSet->ColNo(KColVersion), *version);
    aView.SetColL(iColSet->ColNo(KColSmlTryCount), aPkg.iSmlTryCount);
    aView.SetColL(iColSet->ColNo(KColSessionType), aPkg.iSessionType);
    aView.SetColL(iColSet->ColNo(KColIapId), aPkg.iIapId);
    aView.SetColL(iColSet->ColNo(KColPkgSize), aPkg.iPkgSize);
    aView.SetColL(iColSet->ColNo(KColUpdateLtr), aPkg.iUpdateLtr);

    RDbColWriteStream wstream;
    CleanupClosePushL(wstream);
    wstream.OpenL(aView, iColSet->ColNo(KColPkgUrl));
    // Cannot write 8 bit descriptors to databae
    HBufC* buf = HBufC::NewLC(aPkgURL.Length());
    buf->Des().Copy(aPkgURL);
    wstream.WriteL(buf->Des());

    FLOG(_L("CFotaDB::StateToRowL  id:%d result:%d state:%d profileid:%d \
    		name:%d chars version: %d chars url: %d chars sessiontype:%d iapid:%d pkgsize:%d updateltr = %d"),
            aPkg.iPkgId, aPkg.iResult, aPkg.iState, aPkg.iProfileId,
            pkgname->Des().Length(), version->Des().Length(),
            buf->Des().Length(), aPkg.iSessionType, aPkg.iIapId,
            aPkg.iPkgSize, aPkg.iUpdateLtr);

    CleanupStack::PopAndDestroy(buf);
    CleanupStack::PopAndDestroy(&wstream);
    CleanupStack::PopAndDestroy(version);
    CleanupStack::PopAndDestroy(pkgname);
    }