INT_PTR ModulesDlg::OnUnload( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    // Get selection
    auto idx = _modList.selection();
    if (idx == MAXUINT)
        idx = 0;

    if (_process.valid())
    {
        wchar_t* pEnd = nullptr;
        blackbone::module_t modBase = wcstoull( _modList.itemText( idx, ImageBase ).c_str(), &pEnd, 0x10 );
        auto mod = _process.modules().GetModule( modBase );
        auto barrier = _process.core().native()->GetWow64Barrier();

        // Validate module
        if (barrier.type == blackbone::wow_32_32 && mod->type == blackbone::mt_mod64)
        {
            Message::ShowError( hDlg, L"Please use solomon64.exe to unload 64 bit modules from WOW64 process" );
            return TRUE;
        }

        if (mod != nullptr)
        {
            _process.modules().Unload( mod );
            RefreshList();
        }
        else
            Message::ShowError( hDlg, L"Module not found" );
    }

    return TRUE;
}