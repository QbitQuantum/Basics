manager::~manager()
{
#ifdef CAIRO_HAS_FT_FONT
    FcConfigAppFontClear(FcConfigGetCurrent());
#endif

#if CAIRO_HAS_WIN32_FONT
    for(const std::string& path : filesystem::get_binary_paths("fonts")) {
        std::vector<std::string> files;
        if(filesystem::is_directory(path))
            filesystem::get_files_in_dir(path, &files, nullptr, filesystem::ENTIRE_FILE_PATH);
        for(const std::string& file : files) {
            if(file.substr(file.length() - 4) == ".ttf" || file.substr(file.length() - 4) == ".ttc")
            {
                const std::wstring wfile = unicode_cast<std::wstring>(file);
                RemoveFontResourceExW(wfile.c_str(), FR_PRIVATE, nullptr);
            }
        }
    }
#endif
}