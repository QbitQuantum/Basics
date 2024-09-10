ECode IconPackHelper::CreateIconResource(
    /* [in] */ IContext* context,
    /* [in] */ const String& packageName,
    /* [out] */ IResources** iconRes)
{
    VALIDATE_NOT_NULL(iconRes);
    AutoPtr<IPackageManager> pm;
    context->GetPackageManager((IPackageManager**)&pm);
    AutoPtr<IPackageInfo> info;
    FAIL_RETURN(pm->GetPackageInfo(packageName, 0, (IPackageInfo**)&info))
    AutoPtr<IApplicationInfo> appInfo;
    info->GetApplicationInfo((IApplicationInfo**)&appInfo);
    String themeApk;
    appInfo->GetPublicSourceDir(&themeApk);

    String prefixPath;
    String iconPkgPath;
    String iconResPath;
    Boolean result;
    if (info->GetIsLegacyIconPackPkg(&result), result) {
        iconResPath = "";
        iconPkgPath = "";
        prefixPath = "";
    }
    else {
        prefixPath = IThemeUtils::ICONS_PATH; //path inside APK
        iconPkgPath = ThemeUtils::GetIconPackPkgPath(packageName);
        iconResPath = ThemeUtils::GetIconPackResPath(packageName);
    }

    AutoPtr<IAssetManager> assets;
    CAssetManager::New((IAssetManager**)&assets);
    Int32 cookie;
    assets->AddIconPath(themeApk, iconPkgPath,
            prefixPath, IResources::THEME_ICON_PKG_ID, &cookie);

    AutoPtr<IResources> res;
    context->GetResources((IResources**)&res);
    AutoPtr<IDisplayMetrics> dm;
    res->GetDisplayMetrics((IDisplayMetrics**)&dm);
    AutoPtr<IConfiguration> config;
    res->GetConfiguration((IConfiguration**)&config);
    return CResources::New(assets, dm, config, iconRes);
}