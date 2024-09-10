/**
 * Display an "open file" dialog
 */
void GD_EXTENSION_API ShowOpenFile( RuntimeScene & scene, gd::Variable & variable, const gd::String & title, gd::String filters )
{
    sf::Clock timeSpent;

    gd::String result;

    //Display the dialog
    #if defined(WINDOWS)
    //Process filters to match windows dialogs filters style.
    filters.Raw() = filters.Raw()+'\0';
    std::replace(filters.Raw().begin(), filters.Raw().end(), '|', '\0');

    OPENFILENAMEW toGetFileName; //Struct for the dialog
    wchar_t filePath[MAX_PATH];
    _wgetcwd(filePath, MAX_PATH);

    ZeroMemory(&toGetFileName, sizeof(OPENFILENAMEW));
    toGetFileName.lStructSize = sizeof(OPENFILENAMEW);
    toGetFileName.hwndOwner = NULL;
    toGetFileName.lpstrFile = filePath;
    toGetFileName.nMaxFile = MAX_PATH;
    toGetFileName.lpstrFilter = filters == "\0" ? NULL : filters.ToWide().c_str();
    toGetFileName.nFilterIndex = 1;
    toGetFileName.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;;

    if(GetOpenFileNameW(&toGetFileName) == TRUE)
        result = gd::String::FromWide(filePath);
    #endif
    #if defined(LINUX) || defined(MACOS)
    std::string strResult;
    nw::OpenFile * dialog = new nw::OpenFile(title.ToLocale(), true, strResult);
    dialog->wait_until_closed();
    result = gd::String::FromLocale(strResult);
    #endif

    scene.GetTimeManager().NotifyPauseWasMade(timeSpent.getElapsedTime().asMicroseconds());//Don't take the time spent in this function in account.

    //Update the variable
    variable.SetString(result);
}