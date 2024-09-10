bool DropMoveCommand::Execute()
{
    CString droppath = parser.GetVal(L"droptarget");
    if (CTSVNPath(droppath).IsAdminDir())
        return FALSE;
    SVN svn;
    unsigned long count = 0;
    pathList.RemoveAdminPaths();
    CString sNewName;
    if ((parser.HasKey(L"rename"))&&(pathList.GetCount()==1))
    {
        // ask for a new name of the source item
        CRenameDlg renDlg;
        renDlg.SetFileSystemAutoComplete();
        renDlg.SetInputValidator(this);
        renDlg.m_windowtitle.LoadString(IDS_PROC_MOVERENAME);
        renDlg.m_name = pathList[0].GetFileOrDirectoryName();
        if (renDlg.DoModal() != IDOK)
        {
            return FALSE;
        }
        sNewName = renDlg.m_name;
    }
    CProgressDlg progress;
    if (progress.IsValid())
    {
        progress.SetTitle(IDS_PROC_MOVING);
        progress.SetTime(true);
        progress.ShowModeless(CWnd::FromHandle(GetExplorerHWND()));
    }
    UINT msgRet = IDNO;
    INT_PTR msgRetNonversioned = 0;
    for (int nPath = 0; nPath < pathList.GetCount(); nPath++)
    {
        CTSVNPath destPath;
        if (sNewName.IsEmpty())
            destPath = CTSVNPath(droppath+L"\\"+pathList[nPath].GetFileOrDirectoryName());
        else
            destPath = CTSVNPath(droppath+L"\\"+sNewName);
        // path the same but case-changed is ok: results in a case-rename
        if (!(pathList[nPath].IsEquivalentToWithoutCase(destPath) && !pathList[nPath].IsEquivalentTo(destPath)))
        {
            if (destPath.Exists())
            {
                progress.Stop();

                CString name = pathList[nPath].GetFileOrDirectoryName();
                if (!sNewName.IsEmpty())
                    name = sNewName;
                progress.Stop();
                CRenameDlg dlg;
                dlg.SetFileSystemAutoComplete();
                dlg.SetInputValidator(this);
                dlg.m_name = name;
                dlg.m_windowtitle.Format(IDS_PROC_NEWNAMEMOVE, (LPCTSTR)name);
                if (dlg.DoModal() != IDOK)
                {
                    return FALSE;
                }
                destPath.SetFromWin(droppath+L"\\"+dlg.m_name);

                progress.EnsureValid();
                progress.SetTitle(IDS_PROC_MOVING);
                progress.SetTime(true);
                progress.SetProgress(count, pathList.GetCount());
                progress.ShowModeless(CWnd::FromHandle(GetExplorerHWND()));
            }
        }
        if (!svn.Move(CTSVNPathList(pathList[nPath]), destPath))
        {
            if ((svn.GetSVNError() && svn.GetSVNError()->apr_err == SVN_ERR_ENTRY_EXISTS) && (destPath.Exists()))
            {
                if ((msgRet != IDYESTOALL) && (msgRet != IDNOTOALL))
                {
                    progress.Stop();
                    // target file already exists. Ask user if he wants to replace the file
                    CString sReplace;
                    sReplace.Format(IDS_PROC_REPLACEEXISTING, destPath.GetWinPath());
                    CTaskDialog taskdlg(sReplace,
                                        CString(MAKEINTRESOURCE(IDS_PROC_REPLACEEXISTING_TASK2)),
                                        L"TortoiseSVN",
                                        0,
                                        TDF_USE_COMMAND_LINKS | TDF_ALLOW_DIALOG_CANCELLATION | TDF_POSITION_RELATIVE_TO_WINDOW | TDF_SIZE_TO_CONTENT);
                    taskdlg.AddCommandControl(1, CString(MAKEINTRESOURCE(IDS_PROC_REPLACEEXISTING_TASK3)));
                    taskdlg.AddCommandControl(2, CString(MAKEINTRESOURCE(IDS_PROC_REPLACEEXISTING_TASK4)));
                    taskdlg.SetCommonButtons(TDCBF_CANCEL_BUTTON);
                    taskdlg.SetVerificationCheckboxText(CString(MAKEINTRESOURCE(IDS_PROC_REPLACEEXISTING_TASK5)));
                    taskdlg.SetVerificationCheckbox(false);
                    taskdlg.SetDefaultCommandControl(2);
                    taskdlg.SetMainIcon(TD_WARNING_ICON);
                    INT_PTR ret = taskdlg.DoModal(GetExplorerHWND());
                    if (ret == 1) // replace
                        msgRet = taskdlg.GetVerificationCheckboxState() ? IDYESTOALL : IDYES;
                    else
                        msgRet = taskdlg.GetVerificationCheckboxState() ? IDNOTOALL : IDNO;

                    progress.EnsureValid();
                    progress.SetTitle(IDS_PROC_MOVING);
                    progress.SetTime(true);
                    progress.SetProgress(count, pathList.GetCount());
                    progress.ShowModeless(CWnd::FromHandle(GetExplorerHWND()));
                }

                if ((msgRet == IDYES) || (msgRet == IDYESTOALL))
                {
                    if (!svn.Remove(CTSVNPathList(destPath), true, false))
                    {
                        destPath.Delete(true);
                    }
                    if (!svn.Move(CTSVNPathList(pathList[nPath]), destPath))
                    {
                        progress.Stop();
                        svn.ShowErrorDialog(GetExplorerHWND(), pathList[nPath]);
                        return FALSE;       //get out of here
                    }
                    CShellUpdater::Instance().AddPathForUpdate(destPath);
                }
            }
            else if (svn.GetSVNError() && svn.GetSVNError()->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
            {
                INT_PTR ret = 0;
                if (msgRetNonversioned == 0)
                {
                    progress.Stop();

                    CString sReplace;
                    sReplace.Format(IDS_PROC_MOVEUNVERSIONED_TASK1, destPath.GetWinPath());
                    CTaskDialog taskdlg(sReplace,
                                        CString(MAKEINTRESOURCE(IDS_PROC_MOVEUNVERSIONED_TASK2)),
                                        L"TortoiseSVN",
                                        TDCBF_CANCEL_BUTTON,
                                        TDF_USE_COMMAND_LINKS | TDF_ALLOW_DIALOG_CANCELLATION | TDF_POSITION_RELATIVE_TO_WINDOW | TDF_SIZE_TO_CONTENT);
                    taskdlg.AddCommandControl(101, CString(MAKEINTRESOURCE(IDS_PROC_MOVEUNVERSIONED_TASK3)));
                    taskdlg.AddCommandControl(102, CString(MAKEINTRESOURCE(IDS_PROC_MOVEUNVERSIONED_TASK4)));
                    taskdlg.AddCommandControl(103, CString(MAKEINTRESOURCE(IDS_PROC_MOVEUNVERSIONED_TASK5)));
                    taskdlg.SetVerificationCheckboxText(CString(MAKEINTRESOURCE(IDS_PROC_MOVEUNVERSIONED_TASK6)));
                    taskdlg.SetVerificationCheckbox(false);
                    taskdlg.SetDefaultCommandControl(103);
                    taskdlg.SetMainIcon(TD_WARNING_ICON);
                    ret = taskdlg.DoModal(GetExplorerHWND());
                    if (taskdlg.GetVerificationCheckboxState())
                        msgRetNonversioned = ret;

                    progress.EnsureValid();
                    progress.SetTitle(IDS_PROC_MOVING);
                    progress.SetTime(true);
                    progress.SetProgress(count, pathList.GetCount());
                    progress.ShowModeless(CWnd::FromHandle(GetExplorerHWND()));
                }
                else
                {
                    ret = msgRetNonversioned;
                }
                switch (ret)
                {
                    case 101: // move
                        MoveFile(pathList[nPath].GetWinPath(), destPath.GetWinPath());
                        break;
                    case 102: // move and add
                        MoveFile(pathList[nPath].GetWinPath(), destPath.GetWinPath());
                        if (!svn.Add(CTSVNPathList(destPath), NULL, svn_depth_infinity, true, false, false, false))
                        {
                            progress.Stop();
                            svn.ShowErrorDialog(GetExplorerHWND(), destPath);
                            return FALSE;       //get out of here
                        }
                        break;
                    case 103: // skip
                    default:
                        break;
                }
            }
            else
            {
                progress.Stop();
                svn.ShowErrorDialog(GetExplorerHWND(), pathList[nPath]);
                return FALSE;       //get out of here
            }
        }
        else
            CShellUpdater::Instance().AddPathForUpdate(destPath);
        count++;
        if (progress.IsValid())
        {
            progress.FormatPathLine(1, IDS_PROC_MOVINGPROG, pathList[nPath].GetWinPath());
            progress.FormatPathLine(2, IDS_PROC_CPYMVPROG2, destPath.GetWinPath());
            progress.SetProgress(count, pathList.GetCount());
        }
        if ((progress.IsValid())&&(progress.HasUserCancelled()))
        {
            progress.Stop();
            TaskDialog(GetExplorerHWND(), AfxGetResourceHandle(), MAKEINTRESOURCE(IDS_APPNAME), MAKEINTRESOURCE(IDS_SVN_USERCANCELLED), NULL, TDCBF_OK_BUTTON, TD_INFORMATION_ICON, NULL);
            return FALSE;
        }
    }
    return true;
}