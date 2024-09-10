bool VT::ensure_path_exist( const std::wstring& path )
{
    std::wstring folder = path.substr(0, path.rfind(VT_SLASH));
    SHCreateDirectoryExW(NULL, folder.c_str(), NULL);

    return true;
}