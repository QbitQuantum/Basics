void AppLauncherDlg::OnInitDialog()
{
    USES_CONVERSION;
    nsCOMPtr<nsIMIMEInfo> mimeInfo;
    nsCAutoString url;
    if (mHelperAppLauncher)
    {
        mHelperAppLauncher->GetMIMEInfo(getter_AddRefs(mimeInfo));
        nsCOMPtr<nsIURI> uri;
        mHelperAppLauncher->GetSource(getter_AddRefs(uri));
        uri->GetSpec(url);
    }
    nsMIMEInfoHandleAction prefAction = nsIMIMEInfo::saveToDisk;
    nsAutoString appName;
    nsCAutoString contentType;
    if (mimeInfo)
    {
        mimeInfo->GetPreferredAction(&prefAction);
        mimeInfo->GetApplicationDescription(appName);
        mimeInfo->GetMIMEType(contentType);
    }
    if (prefAction == nsIMIMEInfo::saveToDisk)
    {
        CheckRadioButton(mHwndDlg, IDC_OPENWITHAPP, IDC_SAVETOFILE, IDC_SAVETOFILE);
    }
    else
    {
        CheckRadioButton(mHwndDlg, IDC_OPENWITHAPP, IDC_SAVETOFILE, IDC_OPENWITHAPP);
    }
    SetDlgItemText(mHwndDlg, IDC_URL,
        url.IsEmpty() ? _T("") : A2CT(url.get()));
    SetDlgItemText(mHwndDlg, IDC_APPLICATION,
        appName.IsEmpty() ? _T("<No Application>") : W2CT(appName.get()));
    SetDlgItemText(mHwndDlg, IDC_CONTENTTYPE,
        contentType.IsEmpty() ? _T("") : A2CT(contentType.get()));
}