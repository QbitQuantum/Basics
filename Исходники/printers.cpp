HRESULT WINAPI CPrintersExtractIconW::Initialize(LPCITEMIDLIST pidl)
{
    pidl = ILClone(pidl);

    pdump(pidl);
    return S_OK;
}