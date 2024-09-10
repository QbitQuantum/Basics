static HRESULT GetSplitter(MediaDetImpl *This)
{
    IFileSourceFilter *file;
    LPOLESTR name;
    AM_MEDIA_TYPE mt;
    GUID type[2];
    IFilterMapper2 *map;
    IEnumMoniker *filters;
    IMoniker *mon;
    VARIANT var;
    GUID clsid;
    IBaseFilter *splitter;
    IEnumPins *pins;
    IPin *source_pin, *splitter_pin;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IFilterMapper2, (void **) &map);
    if (FAILED(hr))
        return hr;

    hr = IBaseFilter_QueryInterface(This->source, &IID_IFileSourceFilter,
                                    (void **) &file);
    if (FAILED(hr))
    {
        IFilterMapper2_Release(map);
        return hr;
    }

    hr = IFileSourceFilter_GetCurFile(file, &name, &mt);
    IFileSourceFilter_Release(file);
    CoTaskMemFree(name);
    if (FAILED(hr))
    {
        IFilterMapper2_Release(map);
        return hr;
    }
    type[0] = mt.majortype;
    type[1] = mt.subtype;
    CoTaskMemFree(mt.pbFormat);

    hr = IFilterMapper2_EnumMatchingFilters(map, &filters, 0, TRUE,
                                            MERIT_UNLIKELY, FALSE, 1, type,
                                            NULL, NULL, FALSE, TRUE,
                                            0, NULL, NULL, NULL);
    IFilterMapper2_Release(map);
    if (FAILED(hr))
        return hr;

    hr = E_NOINTERFACE;
    while (IEnumMoniker_Next(filters, 1, &mon, NULL) == S_OK)
    {
        hr = GetFilterInfo(mon, &clsid, &var);
        IMoniker_Release(mon);
        if (FAILED(hr))
            continue;

        hr = CoCreateInstance(&clsid, NULL, CLSCTX_INPROC_SERVER,
                              &IID_IBaseFilter, (void **) &splitter);
        if (FAILED(hr))
        {
            VariantClear(&var);
            continue;
        }

        hr = IGraphBuilder_AddFilter(This->graph, splitter, V_BSTR(&var));
        VariantClear(&var);
        This->splitter = splitter;
        if (FAILED(hr))
            goto retry;

        hr = IBaseFilter_EnumPins(This->source, &pins);
        if (FAILED(hr))
            goto retry;
        IEnumPins_Next(pins, 1, &source_pin, NULL);
        IEnumPins_Release(pins);

        hr = IBaseFilter_EnumPins(splitter, &pins);
        if (FAILED(hr))
        {
            IPin_Release(source_pin);
            goto retry;
        }
        IEnumPins_Next(pins, 1, &splitter_pin, NULL);
        IEnumPins_Release(pins);

        hr = IPin_Connect(source_pin, splitter_pin, NULL);
        IPin_Release(source_pin);
        IPin_Release(splitter_pin);
        if (SUCCEEDED(hr))
            break;

retry:
        IBaseFilter_Release(splitter);
        This->splitter = NULL;
    }

    IEnumMoniker_Release(filters);
    if (FAILED(hr))
        return hr;

    return S_OK;
}