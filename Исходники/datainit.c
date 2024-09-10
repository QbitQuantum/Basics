/*** IDataInitialize methods ***/
static HRESULT WINAPI datainit_GetDataSource(IDataInitialize *iface, IUnknown *outer, DWORD clsctx,
                                LPWSTR initstring, REFIID riid, IUnknown **datasource)
{
    static const WCHAR providerW[] = {'P','r','o','v','i','d','e','r','=',0};
    static const WCHAR msdasqlW[] = {'M','S','D','A','S','Q','L',0};
    datainit *This = impl_from_IDataInitialize(iface);
    IDBProperties *dbprops;
    DBPROPSET *propset;
    WCHAR *prov = NULL;
    CLSID provclsid;
    HRESULT hr;

    TRACE("(%p)->(%p 0x%x %s %s %p)\n", This, outer, clsctx, debugstr_w(initstring), debugstr_guid(riid), datasource);

    /* first get provider name */
    provclsid = IID_NULL;
    if (initstring && (prov = strstrW(initstring, providerW)))
    {
        WCHAR *start, *progid;
        int len;

        prov += sizeof(providerW)/sizeof(WCHAR)-1;
        start = prov;
        while (*prov && *prov != ';')
            ++prov;
        TRACE("got provider %s\n", debugstr_wn(start, prov-start));

        len = prov - start;
        progid = CoTaskMemAlloc((len+1)*sizeof(WCHAR));
        if (!progid) return E_OUTOFMEMORY;

        memcpy(progid, start, len*sizeof(WCHAR));
        progid[len] = 0;

        hr = CLSIDFromProgID(progid, &provclsid);
        CoTaskMemFree(progid);
        if (FAILED(hr))
        {
            ERR("provider %s not registered\n", debugstr_wn(start, prov-start));
            return hr;
        }
    }
    else
    {
        hr = CLSIDFromProgID(msdasqlW, &provclsid);
        if (FAILED(hr))
            ERR("ODBC provider for OLE DB not registered\n");
    }

    /* check for provider mismatch if it was specified in init string */
    if (*datasource && prov)
    {
        DBPROPIDSET propidset;
        enum DBPROPENUM prop;
        CLSID initprov;
        ULONG count;

        hr = IUnknown_QueryInterface(*datasource, &IID_IDBProperties, (void**)&dbprops);
        if (FAILED(hr))
        {
            WARN("provider doesn't support IDBProperties\n");
            return hr;
        }

        prop = DBPROP_INIT_DATASOURCE;
        propidset.rgPropertyIDs = &prop;
        propidset.cPropertyIDs = 1;
        propidset.guidPropertySet = DBPROPSET_DBINIT;
        count = 0;
        propset = NULL;
        hr = IDBProperties_GetProperties(dbprops, 1, &propidset, &count, &propset);
        IDBProperties_Release(dbprops);
        if (FAILED(hr))
        {
            WARN("GetProperties failed for datasource, 0x%08x\n", hr);
            return hr;
        }

        TRACE("initial data source provider %s\n", debugstr_w(V_BSTR(&propset->rgProperties[0].vValue)));
        initprov = IID_NULL;
        CLSIDFromProgID(V_BSTR(&propset->rgProperties[0].vValue), &initprov);
        free_dbpropset(count, propset);

        if (!IsEqualIID(&provclsid, &initprov)) return DB_E_MISMATCHEDPROVIDER;
    }

    if (!*datasource)
    {
        if (!IsEqualIID(&provclsid, &IID_NULL))
            hr = CoCreateInstance(&provclsid, outer, clsctx, riid, (void**)datasource);

        if (FAILED(hr) && IsEqualIID(riid, &IID_IDBInitialize))
            hr = create_db_init(datasource);
    }

    /* now set properties */
    if (initstring)
    {
        WCHAR *eq, *start;

        hr = IUnknown_QueryInterface(*datasource, &IID_IDBProperties, (void**)&dbprops);
        if (FAILED(hr))
        {
            WARN("provider doesn't support IDBProperties\n");
            return hr;
        }

        start = initstring;
        while (start && (eq = strchrW(start, '=')))
        {
            static const WCHAR providerW[] = {'P','r','o','v','i','d','e','r',0};
            WCHAR *scol = strchrW(eq+1, ';');
            BSTR value, name;

            name = SysAllocStringLen(start, eq - start);
            /* skip equal sign to get value */
            eq++;
            value = SysAllocStringLen(eq, scol ? scol - eq : -1);

            /* skip semicolon if present */
            if (scol) scol++;
            start = scol;

            if (!strcmpW(name, providerW))
            {
                SysFreeString(name);
                SysFreeString(value);
                continue;
            }

            TRACE("property (name=%s, value=%s)\n", debugstr_w(name), debugstr_w(value));

            hr = set_dbpropset(name, value, &propset);
            SysFreeString(name);
            SysFreeString(value);
            if (FAILED(hr)) break;

            hr = IDBProperties_SetProperties(dbprops, 1, propset);
            free_dbpropset(1, propset);
            TRACE("provider ret 0x%08x\n", hr);
        }

        IDBProperties_Release(dbprops);
    }

    return hr;
}