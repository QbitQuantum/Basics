void CNewTreeConflictEditorDlg::DoModal(HWND parent)
{
    CTSVNPath path = m_conflictInfo->GetPath();
    CString sDialogTitle;
    sDialogTitle.LoadString(IDS_PROC_EDIT_TREE_CONFLICTS);
    sDialogTitle = CCommonAppUtils::FormatWindowTitle(path.GetUIPathString(), sDialogTitle);

    if (!m_conflictInfo->GetTreeResolutionOptions(m_options))
    {
        m_conflictInfo->ShowErrorDialog(parent);
    }

    CString sMainInstruction = m_conflictInfo->GetIncomingChangeSummary();
    CString sContent = m_conflictInfo->GetLocalChangeSummary();

    int button;

    for (SVNConflictOptions::const_iterator it = m_options.begin(); it != m_options.end(); ++it)
    {
        svn_client_conflict_option_id_t id = (*it)->GetId();

        CString optLabel = (*it)->GetLabel();

        CString optDescription((*it)->GetDescription());
        optDescription.SetAt(0, towupper(optDescription[0]));

        AddCommandButton(100 + id, optLabel + L"\n" + optDescription);
    }

    TASKDIALOGCONFIG taskConfig = {0};
    taskConfig.cbSize = sizeof(taskConfig);
    taskConfig.hwndParent = parent;
    taskConfig.dwFlags = TDF_USE_COMMAND_LINKS;
    taskConfig.lpCallbackData = (LONG_PTR) this;
    taskConfig.pfCallback = TaskDialogCallback;
    taskConfig.pszWindowTitle = sDialogTitle;
    taskConfig.pszMainInstruction = sMainInstruction;
    taskConfig.pszContent = sContent;
    taskConfig.pButtons = &m_buttons.front();
    taskConfig.cButtons = (int) m_buttons.size();
    taskConfig.dwCommonButtons = TDCBF_CANCEL_BUTTON;
    TaskDialogIndirect(&taskConfig, &button, NULL, NULL);
    if (button == IDCANCEL)
    {
        m_bCancelled = true;
    }
}