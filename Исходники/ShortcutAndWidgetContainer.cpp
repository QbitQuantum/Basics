ECode ShortcutAndWidgetContainer::constructor(
        /* [in] */ IContext* context)
{
    ViewGroup::constructor(context);

    AutoPtr<IWallpaperManagerHelper> helper;
    CWallpaperManagerHelper::AcquireSingleton((IWallpaperManagerHelper**)&helper);
    return helper->GetInstance(context, (IWallpaperManager**)&mWallpaperManager);
}