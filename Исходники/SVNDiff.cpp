bool SVNDiff::UnifiedDiff(CTSVNPath& tempfile, const CTSVNPath& url1, const SVNRev& rev1, const CTSVNPath& url2, const SVNRev& rev2, const SVNRev& peg, const CString& options, bool bIgnoreAncestry /* = false */, bool bIgnoreProperties /* = true */)
{
    tempfile = CTempFiles::Instance().GetTempFilePath(m_bRemoveTempFiles, CTSVNPath(L"Test.diff"));
    bool bIsUrl = !!SVN::PathIsURL(url1);

    CProgressDlg progDlg;
    progDlg.SetTitle(IDS_APPNAME);
    progDlg.SetLine(1, CString(MAKEINTRESOURCE(IDS_PROGRESS_UNIFIEDDIFF)));
    progDlg.SetTime(false);
    m_pSVN->SetAndClearProgressInfo(&progDlg);
    progDlg.ShowModeless(GetHWND());
    // find the root of the files
    CTSVNPathList plist;
    plist.AddPath(url1);
    plist.AddPath(url2);
    CTSVNPath relativeTo = plist.GetCommonRoot();
    if (!relativeTo.IsUrl())
    {
        if (!relativeTo.IsDirectory())
            relativeTo = relativeTo.GetContainingDirectory();
    }
    if (relativeTo.IsEmpty() && url1.Exists() && url2.IsUrl())
    {
        // the source path exists, i.e. it's a local path, so
        // use this as the relative url
        relativeTo = url1.GetDirectory();
    }
    // the 'relativeTo' path must be a path: svn throws an error if it's used for urls.
    else if ((!url2.IsEquivalentTo(url1) && (relativeTo.IsEquivalentTo(url1) || relativeTo.IsEquivalentTo(url2))) || url1.IsUrl() || url2.IsUrl())
        relativeTo.Reset();
    if ((!url1.IsEquivalentTo(url2))||((rev1.IsWorking() || rev1.IsBase())&&(rev2.IsWorking() || rev2.IsBase())))
    {
        if (!m_pSVN->Diff(url1, rev1, url2, rev2, relativeTo, svn_depth_infinity, true, false, false, false, false, false, bIgnoreProperties, false, options, bIgnoreAncestry, tempfile))
        {
            progDlg.Stop();
            m_pSVN->SetAndClearProgressInfo((HWND)NULL);
            m_pSVN->ShowErrorDialog(GetHWND());
            return false;
        }
    }
    else
    {
        if (!m_pSVN->PegDiff(url1, (peg.IsValid() ? peg : (bIsUrl ? m_headPeg : SVNRev::REV_WC)), rev1, rev2, relativeTo, svn_depth_infinity, true, false, false, false, false, false, bIgnoreProperties, false, options, false, tempfile))
        {
            if (!m_pSVN->Diff(url1, rev1, url2, rev2, relativeTo, svn_depth_infinity, true, false, false, false, false, false, bIgnoreProperties, false, options, false, tempfile))
            {
                progDlg.Stop();
                m_pSVN->SetAndClearProgressInfo((HWND)NULL);
                m_pSVN->ShowErrorDialog(GetHWND());
                return false;
            }
        }
    }
    if (CAppUtils::CheckForEmptyDiff(tempfile))
    {
        progDlg.Stop();
        m_pSVN->SetAndClearProgressInfo((HWND)NULL);
        TaskDialog(GetHWND(), AfxGetResourceHandle(), MAKEINTRESOURCE(IDS_APPNAME), MAKEINTRESOURCE(IDS_ERR_ERROROCCURED), MAKEINTRESOURCE(IDS_ERR_EMPTYDIFF), TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);
        return false;
    }
    progDlg.Stop();
    m_pSVN->SetAndClearProgressInfo((HWND)NULL);
    return true;
}