std::string getCSIDLPath(long csidl){
    CHAR pth[MAX_PATH];
    HRESULT result = SHGetFolderPathA(NULL, csidl, NULL, 0, pth);

    if (result != S_OK)
        return "";
    std::string ret = pth;
    ret+='\\';
    return ret;
}