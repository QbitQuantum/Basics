//
// Function to create an Appx Bundle writer with default settings, given the
// output file name.
//
// Parameters:
// outputFileName - Name including path to the bundle (.appxbundle file) to
//                  be created.
// writer - Output parameter pointing to the created instance of
//          IAppxBundleWriter when this function succeeds.
//
HRESULT GetBundleWriter(
    _In_ LPCWSTR outputFileName,
    _Outptr_ IAppxBundleWriter** writer)
{
    HRESULT hr = S_OK;
    IStream* outputStream = NULL;
    IAppxBundleFactory* appxBundleFactory = NULL;

    // Create a stream over the output file where the bundle will be written
    hr = SHCreateStreamOnFileEx(
            outputFileName,
            STGM_CREATE | STGM_WRITE | STGM_SHARE_EXCLUSIVE,
            0, // default file attributes
            TRUE, // create file if it does not exist
            NULL, // no template
            &outputStream);

    // Create a new Appx Bundle factory
    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(
                __uuidof(AppxBundleFactory),
                NULL,
                CLSCTX_INPROC_SERVER,
                __uuidof(IAppxBundleFactory),
                (LPVOID*)(&appxBundleFactory));
    }

    // Create a new bundle writer using the factory
    if (SUCCEEDED(hr))
    {
        hr = appxBundleFactory->CreateBundleWriter(
                outputStream,
                0, // by specifying 0, the bundle will have an automatically
                   // generated version number based on the current time
                writer);
    }

    // Clean up allocated resources
    if (appxBundleFactory != NULL)
    {
        appxBundleFactory->Release();
        appxBundleFactory = NULL;
    }
    if (outputStream != NULL)
    {
        outputStream->Release();
        outputStream = NULL;
    }
    return hr;
}