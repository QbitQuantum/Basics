Boolean RegisteredServicesCache::InSystemImage(
    /* [in] */ Int32 callerUid)
{
    AutoPtr<IPackageManager> pkgManager;
    mContext->GetPackageManager((IPackageManager**)&pkgManager);
    AutoPtr< ArrayOf<String> > packages;
    pkgManager->GetPackagesForUid(callerUid, (ArrayOf<String>**)&packages);
    for (Int32 i = 0; i < packages->GetLength(); i++) {
        String name = (*packages)[i];
        // try {
        AutoPtr<IPackageInfo> packageInfo;
        if (FAILED(pkgManager->GetPackageInfo(name, 0 /* flags */, (IPackageInfo**)&packageInfo))) {
            return FALSE;
        }
        AutoPtr<IApplicationInfo> appInfo;
        ASSERT_SUCCEEDED(packageInfo->GetApplicationInfo((IApplicationInfo**)&appInfo));
        Int32 flags;
        appInfo->GetFlags(&flags);
        if ((flags & IApplicationInfo::FLAG_SYSTEM) != 0) {
            return TRUE;
        }
        // } catch (PackageManager.NameNotFoundException e) {
        //     return false;
        // }
    }
    return FALSE;
}