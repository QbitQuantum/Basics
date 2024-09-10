bool PasteMoveCommand::Execute()
{
    CString sDroppath = parser.GetVal(L"droptarget");
    CTSVNPath dropPath(sDroppath);
    ProjectProperties props;
    props.ReadProps(dropPath);
    if (dropPath.IsAdminDir())
        return FALSE;
    SVN svn;
    SVNStatus status;
    unsigned long count = 0;
    pathList.RemoveAdminPaths();
    CString sNewName;
    CProgressDlg progress;
    progress.SetTitle(IDS_PROC_MOVING);
    progress.SetTime(true);
    progress.ShowModeless(CWnd::FromHandle(GetExplorerHWND()));
    for(int nPath = 0; nPath < pathList.GetCount(); nPath++)
    {
        CTSVNPath destPath;
        if (sNewName.IsEmpty())
            destPath = CTSVNPath(sDroppath+L"\\"+pathList[nPath].GetFileOrDirectoryName());
        else
            destPath = CTSVNPath(sDroppath+L"\\"+sNewName);
        if (destPath.Exists())
        {
            CString name = pathList[nPath].GetFileOrDirectoryName();
            if (!sNewName.IsEmpty())
                name = sNewName;
            progress.Stop();
            CRenameDlg dlg;
            dlg.SetFileSystemAutoComplete();
            dlg.m_name = name;
            dlg.SetInputValidator(this);
            m_renPath = pathList[nPath];
            dlg.m_windowtitle.Format(IDS_PROC_NEWNAMEMOVE, (LPCTSTR)name);
            if (dlg.DoModal() != IDOK)
            {
                return FALSE;
            }
            destPath.SetFromWin(sDroppath+L"\\"+dlg.m_name);
        }
        svn_wc_status_kind s = status.GetAllStatus(pathList[nPath]);
        if ((s == svn_wc_status_none)||(s == svn_wc_status_unversioned)||(s == svn_wc_status_ignored))
        {
            // source file is unversioned: move the file to the target, then add it
            MoveFile(pathList[nPath].GetWinPath(), destPath.GetWinPath());
            if (!svn.Add(CTSVNPathList(destPath), &props, svn_depth_infinity, true, true, false, true))
            {
                svn.ShowErrorDialog(GetExplorerHWND());
                return FALSE;       //get out of here
            }
            CShellUpdater::Instance().AddPathForUpdate(destPath);
        }
        else
        {
            if (!svn.Move(CTSVNPathList(pathList[nPath]), destPath))
            {
                svn.ShowErrorDialog(GetExplorerHWND());
                return FALSE;       //get out of here
            }
            else
                CShellUpdater::Instance().AddPathForUpdate(destPath);
        }
        count++;
        if (progress.IsValid())
        {
            progress.FormatPathLine(1, IDS_PROC_MOVINGPROG, pathList[nPath].GetWinPath());
            progress.FormatPathLine(2, IDS_PROC_CPYMVPROG2, destPath.GetWinPath());
            progress.SetProgress(count, pathList.GetCount());
        }
        if ((progress.IsValid())&&(progress.HasUserCancelled()))
        {
            TaskDialog(GetExplorerHWND(), AfxGetResourceHandle(), MAKEINTRESOURCE(IDS_APPNAME), MAKEINTRESOURCE(IDS_SVN_USERCANCELLED), NULL, TDCBF_OK_BUTTON, TD_INFORMATION_ICON, NULL);
            return FALSE;
        }
    }
    return true;
}