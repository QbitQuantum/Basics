bool MoveToTrash::exec() const
{
    HRESULT result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if (!SUCCEEDED(result))
        return false;

    IFileOperation *fo = nullptr;
    result = CoCreateInstance(CLSID_FileOperation, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&fo));

    if (!SUCCEEDED(result)) {
        CoUninitialize();
        return false;
    }

    ulong flags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;

//    if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS8)
//        flags |= FOFX_RECYCLEONDELETE;

    result = fo->SetOperationFlags(flags);

    if (SUCCEEDED(result)) {
        IShellItem *iShellItem = nullptr;
        result = SHCreateItemFromParsingName(path.toStdWString().c_str(), nullptr, IID_PPV_ARGS(&iShellItem));

        if (SUCCEEDED(result)) {
            result = fo->DeleteItem(iShellItem, nullptr);
            iShellItem->Release();
        }

        if (SUCCEEDED(result))
            result = fo->PerformOperations();
    }

    fo->Release();
    CoUninitialize();

    return SUCCEEDED(result);
}