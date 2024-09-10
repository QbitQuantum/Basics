ECode NetworkPolicyManager::IsUidValidForPolicy(
    /* [in] */ IContext* context,
    /* [in] */ Int32 uid,
    /* [out] */ Boolean* result)
{
    VALIDATE_NOT_NULL(result);

    //first, quick-reject non-applications
    if (!(CUserHandle::IsApp(uid))) {
        *result = FALSE;
    }

    if (!ALLOW_PLATFORM_APP_POLICY) {
        AutoPtr<IPackageManager> pm;
        context->GetPackageManager((IPackageManager**)&pm);
        AutoPtr<IHashSet> systemSignature;
        CHashSet::New((IHashSet**)&systemSignature);
            //try {
        AutoPtr<IPackageInfo> packageinfo;
        ECode ec = pm->GetPackageInfo(String("android"), IPackageManager::GET_SIGNATURES, (IPackageInfo**)&packageinfo);
        if (FAILED(ec)) {
            if (ec == (ECode)E_NAME_NOT_FOUND_EXCEPTION) {
                Logger::E("NetworkPolicyManager", "problem finding system signature");
                return E_RUNTIME_EXCEPTION;
            }
            return NOERROR;
        }
        AutoPtr< ArrayOf<ISignature*> > signatures;
        packageinfo->GetSignatures((ArrayOf<ISignature*>**)&signatures);
        AutoPtr<ISets> sets;
        // TODO: Waiting for Sets
        assert(0);
        // CSets::AcquireSingleton((ISets**)&sets);
        // sets->NewHashSet(signatures, (IHashSet**)&systemSignature);
            // } catch (NameNotFoundException e) {
            // }
            // try {
        // reject apps signed with platform cert
        AutoPtr< ArrayOf<String> > uids;
        pm->GetPackagesForUid(uid, (ArrayOf<String>**)&uids);
        for (Int32 i = 0; i< uids->GetLength(); i++) {
            AutoPtr<IHashSet> packageSignature;
            CHashSet::New((IHashSet**)&packageSignature);
            AutoPtr<IPackageInfo> Uidspackageinfo;
            ECode ec = pm->GetPackageInfo((*uids)[i], IPackageManager::GET_SIGNATURES, (IPackageInfo**)&Uidspackageinfo);
            if (FAILED(ec) && ec != (ECode)E_NAME_NOT_FOUND_EXCEPTION) return ec;

            AutoPtr< ArrayOf<ISignature*> > Uidssignatures;
            packageinfo->GetSignatures((ArrayOf<ISignature*>**)&Uidssignatures);
            for (Int32 j = 0; j< Uidssignatures->GetLength(); j++) {
                packageSignature->Add((*Uidssignatures)[i]);
            }
            Boolean bol;
            packageSignature->ContainsAll(ICollection::Probe(systemSignature), &bol);
            if (bol) {
                *result = FALSE;
                return NOERROR;
            }
        }
            // } catch (NameNotFoundException e) {
            // }
    }

    //nothing found above; we can apply policy to UID
    *result = TRUE;
    return NOERROR;
}