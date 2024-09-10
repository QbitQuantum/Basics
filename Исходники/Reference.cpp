Reference *
Reference::newReference (IUnknown *pOrig, const Interface *pInterface)
{
    if (pOrig == 0) {
        _com_issue_error(E_POINTER);
    }

    if (pInterface == 0) {
        pInterface = findInterfaceFromDispatch(pOrig);
    }

    // If we know it's a custom interface, then query for an interface pointer
    // to that interface, otherwise query for an IUnknown interface.
    const IID &iid = (pInterface == 0) ? IID_IUnknown : pInterface->iid();

    IUnknown *pUnknown;
    HRESULT hr = pOrig->QueryInterface(
        iid,
        reinterpret_cast<void **>(&pUnknown));
    if (FAILED(hr)) {
        pUnknown = pOrig;
        pUnknown->AddRef();
    }

    return new Reference(pUnknown, pInterface);
}