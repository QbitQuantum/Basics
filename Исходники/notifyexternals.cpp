public:
    ApartmentTearDownHandler(HRESULT& hr)
    {
        CONTRACTL
        {
            NOTHROW;
            GC_TRIGGERS;
            MODE_ANY;
        }
        CONTRACTL_END;

        GCX_PREEMP();
        
        m_pMarshalerObj = NULL;
        m_cbRefCount = 1;     
        hr = CoCreateFreeThreadedMarshaler(this, &m_pMarshalerObj);
        if (hr == S_OK)
            m_cbRefCount = 0;
        else
            Release();        
    }

    virtual ~ApartmentTearDownHandler()
    {
        CONTRACTL
        {
            NOTHROW;
            GC_TRIGGERS;
            MODE_ANY;
        }
        CONTRACTL_END;