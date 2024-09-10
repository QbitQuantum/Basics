int wxDirDialog::ShowIFileDialog(WXHWND owner)
{
    HRESULT hr;
    wxCOMPtr<IFileDialog> fileDialog;

    hr = ::CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER,
                            wxIID_PPV_ARGS(IFileDialog, &fileDialog));
    if ( FAILED(hr) )
    {
        wxLogApiError(wxS("CoCreateInstance(CLSID_FileOpenDialog)"), hr);
        return wxID_NONE;
    }

    // allow user to select only a file system folder
    hr = fileDialog->SetOptions(FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM);
    if ( FAILED(hr) )
    {
        wxLogApiError(wxS("IFileDialog::SetOptions"), hr);
        return wxID_NONE;
    }

    hr = fileDialog->SetTitle(m_message.wc_str());
    if ( FAILED(hr) )
    {
        // This error is not serious, let's just log it and continue even
        // without the title set.
        wxLogApiError(wxS("IFileDialog::SetTitle"), hr);
    }

    // set the initial path
    if ( !m_path.empty() )
    {
        // We need to link SHCreateItemFromParsingName() dynamically as it's
        // not available on pre-Vista systems.
        typedef HRESULT
        (WINAPI *SHCreateItemFromParsingName_t)(PCWSTR,
                                                IBindCtx*,
                                                REFIID,
                                                void**);

        SHCreateItemFromParsingName_t pfnSHCreateItemFromParsingName = NULL;
        wxDynamicLibrary dllShell32;
        if ( dllShell32.Load(wxS("shell32.dll"), wxDL_VERBATIM | wxDL_QUIET) )
        {
            wxDL_INIT_FUNC(pfn, SHCreateItemFromParsingName, dllShell32);
        }

        if ( !pfnSHCreateItemFromParsingName )
        {
            wxLogLastError(wxS("SHCreateItemFromParsingName() not found"));
            return wxID_NONE;
        }

        wxCOMPtr<IShellItem> folder;
        hr = pfnSHCreateItemFromParsingName(m_path.wc_str(),
                                              NULL,
                                              wxIID_PPV_ARGS(IShellItem,
                                                             &folder));

        // Failing to parse the folder name is not really an error, we'll just
        // ignore the initial directory in this case, but we should still show
        // the dialog.
        if ( FAILED(hr) )
        {
            if ( hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) )
            {
                wxLogApiError(wxS("SHCreateItemFromParsingName"), hr);
                return wxID_NONE;
            }
        }
        else // The folder was parsed correctly.
        {
            hr = fileDialog->SetFolder(folder);
            if ( FAILED(hr) )
            {
                wxLogApiError(wxS("IFileDialog::SetFolder"), hr);
                return wxID_NONE;
            }
        }
    }


    wxString path;

    hr = fileDialog->Show(owner);
    if ( SUCCEEDED(hr) )
    {
        wxCOMPtr<IShellItem> folder;

        hr = fileDialog->GetResult(&folder);
        if ( SUCCEEDED(hr) )
        {
            LPOLESTR pathOLE = NULL;

            hr = folder->GetDisplayName(SIGDN_FILESYSPATH, &pathOLE);
            if ( SUCCEEDED(hr) )
            {
                path = pathOLE;
                CoTaskMemFree(pathOLE);
            }
            else
            {
                wxLogApiError(wxS("IShellItem::GetDisplayName"), hr);
            }
        }
        else
        {
            wxLogApiError(wxS("IFileDialog::GetResult"), hr);
        }
    }
    else if ( hr == HRESULT_FROM_WIN32(ERROR_CANCELLED) )
    {
        return wxID_CANCEL; // the user cancelled the dialog
    }
    else
    {
        wxLogApiError(wxS("IFileDialog::Show"), hr);
    }

    if ( path.empty() )
    {
        // the user didn't cancel the dialog and yet the path is empty
        // it means there was an error, already logged by wxLogApiError()
        // now report the error to the user and return
        wxLogSysError(_("Couldn't obtain folder name"), hr);
        return wxID_CANCEL;
    }

    m_path = path;
    return wxID_OK;
}