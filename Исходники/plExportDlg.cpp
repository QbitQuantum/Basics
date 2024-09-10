void plExportDlgImp::IDoExport()
{
    fExporting = true;

    // Hide the window, since we don't get control back until the export is done
    ShowWindow(fDlg, SW_HIDE);

    // Do the export
    wchar_t exportPathTEMP[MAX_PATH];
    GetDlgItemTextW(fDlg, IDC_CLIENT_PATH, exportPathTEMP, arrsize(exportPathTEMP));
    plFileName exportPath = plFileName::Join(plString::FromWchar(exportPathTEMP), "Export.prd");

    // For export time stats
    DWORD exportTime = timeGetTime();

    if (fExportFile)
        IExportCurrentFile(exportPath.AsString().c_str());
    else
    {
        std::vector<plFileName> sources = plFileSystem::ListDir(fExportSourceDir, "*.max");
        for (auto iter = sources.begin(); iter != sources.end(); ++iter)
        {
            if (GetCOREInterface()->LoadFromFile(iter->AsString().c_str()))
                IExportCurrentFile(exportPath.AsString().c_str());
        }
    }

    fLastExportTime = (timeGetTime() - exportTime) / 1000;

    IDestroy();

    fExporting = false;
}