    void excelreader::InstanceExcelWorkbook(int visible)
    {
        // get CLSID of excel
        CLSID clsid;
        HRESULT hr = CLSIDFromProgID(L"Excel.Application", &clsid);
        if (FAILED(hr))
        {
            throw ExcelException("start excel failed. confirm excel installed");
        }

        // instance app
       // hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER,
       //                       IID_IDispatch, (void **)&pXlApp);
		hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&pXlApp);
        if (FAILED(hr))
        {
            throw ExcelException("start excel failed. confirm excel installed");
        }

        // display, set Application.Visible to 1
        _variant_t x((long)visible);
        AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlApp, L"Visible", 1, (VARIANT)x);

        // get workbooks
        _variant_t result;
        AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"Workbooks", 0);
        pXlBooks = result.Detach().pdispVal;
    }