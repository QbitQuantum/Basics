int
main(int argc, char **argv)
{
    HRESULT hr;
    CallbackHandler callbackHandler;
    IBindStatusCallback* pBindStatusCallback = nullptr;

    callbackHandler.QueryInterface(IID_IBindStatusCallback, reinterpret_cast<void**>(&pBindStatusCallback));
    DeleteUrlCacheEntryA(argv[1]);
    std::cout << "Resource: " << argv[1] << std::endl;
    hr = URLDownloadToFileA(nullptr, argv[1], argv[2], 0, pBindStatusCallback);
    return hr == S_OK ? EXIT_SUCCESS : EXIT_FAILURE;
}