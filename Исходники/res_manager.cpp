Resource loadResourceWin32(int name) {
    HMODULE handle = GetModuleHandle(L"jsrdbg");
    HRSRC rc = FindResourceW(handle, MAKEINTRESOURCE(name), RT_RCDATA);
    if (rc == nullptr) {
        auto errnum = GetLastError();
        throw std::runtime_error("Failed loading resource: " + systemErrorString(errnum));
    }
    HGLOBAL rcData = LoadResource(handle, rc);
    auto len = SizeofResource(handle, rc);
    auto addr = static_cast<void*>(LockResource(rcData));
    return Resource(addr, len);
}