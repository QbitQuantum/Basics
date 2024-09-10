/** Devpak installation quiet mode
*  This procedure installs the devpak without any of the GUI
*  windows. Used for command line option /quiet
*/
bool InstallDevPak::DoSilentInstall(wxFileName filename)
{
    // Procedure
    // =========
    // 1. Prompt for devpak file to install
    // 2. Extract the devpak INI descriptor
    // 3. Parse the INI descriptor for the files/directories to install
    // 4. Replace any macros in the directory names
    // 5. Extract the files/directories from the devpak archive

    // wxFileName filename(wxFileSelector(wxT("Choose a devpak to open"),"","","", wxT("All supported package formats (*.DevPak) |*.devpak|All files (*.*)|*.*")));
    if ( filename.FileExists() )
    {
        // work with the file
        wxString archiveFile;
        wxString archiveDir = filename.GetPath();

        if (archiveDir.IsEmpty()) { // If empty, then we are in the current working directory
            archiveDir = ::wxGetCwd();
            archiveFile = ::wxGetCwd() + wxFILE_SEP_PATH + filename.GetFullPath();
        } else
            archiveFile = filename.GetFullPath();

        // Get a temporary directory to unpack things
        ::wxSetWorkingDirectory(wxStandardPaths::Get().GetTempDir());

        DevPakInfo info;

        if (!InstallDevPak::GetPackageInfo(&info, archiveFile)) {
            InstallDevPak::ShowLog("No *.DevPackage file found. DevPak format incorrect or corrupted.");
            return false;
        }

        if (!InstallDevPak::ProcessDirs(archiveDir, &info))
            return false;

        wxListBox lbInstalledFiles; // This doesn't get used
        if (!InstallDevPak::ExtractArchive(archiveFile, info, &lbInstalledFiles)) {
            InstallDevPak::ShowLog("Extract archive failed on " + archiveFile);
            return false;
        }

    }
    return true;
}