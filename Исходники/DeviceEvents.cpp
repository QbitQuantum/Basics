    IFACEMETHODIMP QueryInterface(
        _In_         REFIID  riid,
        _COM_Outptr_ void**  ppv)
    {
        static const QITAB qitab[] =
        {
            QITABENT(CPortableDeviceEventsCallback, IPortableDeviceEventCallback),
            { },
        };

        return QISearch(this, qitab, riid, ppv);
    }