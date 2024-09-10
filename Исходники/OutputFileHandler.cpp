std::string OutputFileHandler::MakeFoldersAndReturnFullPath(const std::string& rDirectory) const
{
    fs::path output_root(GetChasteTestOutputDirectory());
    fs::path rel_path(rDirectory);

    if (!rel_path.empty() && (*(--rel_path.end())) == ".")
    {
        // rDirectory has a trailing slash, which gives an unhelpful last component
        rel_path.remove_leaf();
    }

    // Make master wait (because other processes may be checking whether a directory exists)
    PetscTools::Barrier("OutputFileHandler::MakeFoldersAndReturnFullPathBeforeCreation");
    // Are we the master process? Only the master should make any new directories
    if (PetscTools::AmMaster())
    {
        try
        {
            // If necessary make the ChasteTestOutputDirectory - don't make it deleteable by Chaste
            fs::create_directories(output_root); // Note that this is a no-op if the folder exists already

            // Now make all the sub-folders requested one-by-one and add the .chaste_deletable_folder file to them
            fs::path next_folder(output_root);
            for (fs::path::iterator path_iter = rel_path.begin(); path_iter != rel_path.end(); ++path_iter)
            {
                next_folder /= *path_iter;
                bool created_dir = fs::create_directory(next_folder);
                if (created_dir)
                {
                    // Add the Chaste signature file
                    fs::ofstream sig_file(next_folder / SIG_FILE_NAME);
                    sig_file.close();
                }
            }
        }
        // LCOV_EXCL_START
        catch (const fs::filesystem_error& e)
        {
            TERMINATE("Error making test output folder: " << e.what());
        }
        // LCOV_EXCL_STOP
    }

    // Wait for master to finish before going on to use the directory.
    PetscTools::Barrier("OutputFileHandler::MakeFoldersAndReturnFullPath");

    std::string path_with_slash = (output_root / rel_path).string();
    AddTrailingSlash(path_with_slash);
    return path_with_slash;
}