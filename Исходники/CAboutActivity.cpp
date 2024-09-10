ECode CAboutActivity::OnCreate(
    /* [in] */ IBundle* savedInstanceState)
{
    Logger::D(TAG, "OnCreate()---");
    Activity::OnCreate(savedInstanceState);
    SetContentView(R::layout::activity_about);
    AutoPtr<MyListener> l = new MyListener(this);
    AutoPtr<IView> view = FindViewById(R::id::about_back);
    mBackButton = IImageView::Probe(view);
    assert(mBackButton != NULL);
    mBackButton->SetOnClickListener(l.Get());
    view = FindViewById(R::id::about_version);
    AutoPtr<ITextView> versionView = ITextView::Probe(view);
    assert(versionView != NULL);

    String pkgName, pkgVersion;
    AutoPtr<IPackageManager> pkgMgr;
    AutoPtr<IPackageInfo> pkgInfo;

    GetPackageName(&pkgName);
    GetPackageManager((IPackageManager**)&pkgMgr);
    pkgMgr->GetPackageInfo(pkgName, 0, (IPackageInfo**)&pkgInfo);
    pkgInfo->GetVersionName(&pkgVersion);
    Logger::D(TAG, "OnCreate()---pkgVersion:%s", pkgVersion.string());
    AutoPtr<ICharSequence> cs;
    CStringWrapper::New(pkgVersion, (ICharSequence**)&cs);
    versionView->SetText(cs);

    return NOERROR;
}