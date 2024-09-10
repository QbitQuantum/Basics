fs::path TempFolder::GetNewTempFolderPath()
{
#ifdef _WIN32
    // The specified "c:\\temp" path will only be used
    // when the TMP environment variable is undefined
    // http://msdn.microsoft.com/en-us/library/hs3e7355.aspx
    wchar_t *tmp_name = _wtempnam( L"c:\\temp", L"unused" );
    fs::path main_temp_folder = fs::path( tmp_name ).parent_path();
    free( tmp_name );
#else
    // GCC bitches and moans if we use tempnam(), so
    // we'll just use the P_tmpdir macro. We can't use
    // that on Win because it points to the drive root there
    // instead of the system temp folder
    // http://www.delorie.com/gnu/docs/glibc/libc_295.html
    fs::path main_temp_folder = fs::path( P_tmpdir );
#endif    

    return main_temp_folder / fs::path( FC_TEMP_FOLDER ) / fs::unique_path( UNIQUE_PATH_MODEL );
}