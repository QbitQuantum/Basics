// Creates and returns an Impl object based on the given class ID.
// Will create the appropriate kind of API class and attach it.
//
// Implementation note:  This function does the following:
// 1) Create the API class.  (The API class will create the Impl class
//    and attach it.)
// 2) Ask the newly created API class for its contained Impl class.
// 3) Return that Impl class.
//
ImplAAFRoot * CreateImpl (const aafClassID_t & rClassID)
{
    IAAFRoot	*pIAAFRoot;
    ImplAAFRoot	*implRoot;
    HRESULT		hr;
    CLSID           classID;

    // Cast (by bitwise copy) from aafClassID_t to CLSID.
    //
    memcpy(&classID, &rClassID, sizeof(CLSID));

    // The reference implementation must be "self-contained". We do
    // not want any user supplied classes to be created and used
    // instead on one our built-in classes.
    //
    // The simplest change is to just simulate a call to
    // CoCreateInstance:
    //
    // This code is invoked within the current module so we
    // should just be able to call the DllGetClassObject entry point
    // instead of calling CoCreateInstance and searching the
    // registry.
    IClassFactory *pFactory = NULL;
    hr = DllGetClassObject(classID, IID_IClassFactory, (void **)&pFactory);
    if (SUCCEEDED(hr))
    {
        hr = pFactory->CreateInstance(NULL, IID_IAAFRoot, (void **)&pIAAFRoot);
        pFactory->Release();
    }

    if (SUCCEEDED(hr))
        pIAAFRoot->GetImplRep((void **)&implRoot);
    else
        implRoot = NULL;

    return (implRoot);
}