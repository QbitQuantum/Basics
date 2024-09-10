static nfdresult_t SetDefaultPath( IFileDialog *dialog, const char *defaultPath )
{
    if ( !defaultPath || strlen(defaultPath) == 0 )
        return NFD_OKAY;

    wchar_t *defaultPathW = {0};
    CopyNFDCharToWChar( defaultPath, &defaultPathW );

    IShellItem *folder;
    HRESULT result = SHCreateItemFromParsingName( defaultPathW, NULL, IID_PPV_ARGS(&folder) );

    // Valid non results.
    if ( result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) || result == HRESULT_FROM_WIN32(ERROR_INVALID_DRIVE) )
    {
        NFDi_Free( defaultPathW );
        return NFD_OKAY;
    }

    if ( !SUCCEEDED(result) )
    {
        NFDi_SetError("Error creating ShellItem");
        NFDi_Free( defaultPathW );
        return NFD_ERROR;
    }
    
    // Could also call SetDefaultFolder(), but this guarantees defaultPath -- more consistency across API.
    dialog->SetFolder( folder );

    NFDi_Free( defaultPathW );
    folder->Release();
    
    return NFD_OKAY;
}