bool XmlProfileParser::ParseFile(const char *pszPath, Profile *pProfile, HMODULE hModule)
{
    assert(pszPath != nullptr);
    assert(pProfile != nullptr);

    // import schema from the named resource
    HRSRC hSchemaXmlResource = FindResource(hModule, L"DISKSPD.XSD", RT_HTML);
    assert(hSchemaXmlResource != NULL);
    HGLOBAL hSchemaXml = LoadResource(hModule, hSchemaXmlResource);
    assert(hSchemaXml != NULL);
    LPVOID pSchemaXml = LockResource(hSchemaXml);
    assert(pSchemaXml != NULL);
    
    // convert from utf-8 produced by the xsd authoring tool to utf-16
    int cchSchemaXml = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pSchemaXml, -1, NULL, 0);
	vector<WCHAR> vWideSchemaXml(cchSchemaXml);
    int dwcchWritten = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pSchemaXml, -1, vWideSchemaXml.data(), cchSchemaXml);
    UNREFERENCED_PARAMETER(dwcchWritten);
    assert(dwcchWritten == cchSchemaXml);
    // ... and finally, packed in a bstr for the loadXml interface
    CComBSTR bSchemaXml(vWideSchemaXml.data());

    bool fComInitialized = false;
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr))
    {
        fComInitialized = true;
        CComPtr<IXMLDOMDocument2> spXmlDoc = nullptr;
        CComPtr<IXMLDOMDocument2> spXmlSchema = nullptr;
        CComPtr<IXMLDOMSchemaCollection2> spXmlSchemaColl = nullptr;
        CComPtr<IXMLDOMParseError> spXmlParseError = nullptr;

        // create com objects and decorate
        hr = CoCreateInstance(__uuidof(DOMDocument60), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&spXmlSchema));
        if (SUCCEEDED(hr))
        {
            hr = spXmlSchema->put_async(VARIANT_FALSE);
        }
        if (SUCCEEDED(hr))
        {
            hr = spXmlSchema->setProperty(CComBSTR("ProhibitDTD"), CComVariant(VARIANT_FALSE));
        }
        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(__uuidof(XMLSchemaCache60), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&spXmlSchemaColl));
        }
        if (SUCCEEDED(hr))
        {
            hr = spXmlSchemaColl->put_validateOnLoad(VARIANT_TRUE);
        }
        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(__uuidof(DOMDocument60), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&spXmlDoc));
        }
        if (SUCCEEDED(hr))
        {
            hr = spXmlDoc->put_async(VARIANT_FALSE);
        }
        if (SUCCEEDED(hr))
        {
            hr = spXmlDoc->put_validateOnParse(VARIANT_TRUE);
        }
        if (SUCCEEDED(hr))
        {
            VARIANT_BOOL fvIsOk;
            hr = spXmlSchema->loadXML(bSchemaXml, &fvIsOk);
            if (FAILED(hr) || fvIsOk != VARIANT_TRUE)
            {
                hr = spXmlSchema->get_parseError(&spXmlParseError);
                if (SUCCEEDED(hr))
                {
                    ReportXmlError("schema", spXmlParseError);
                }
                hr = E_FAIL;
            }
        }
		if (SUCCEEDED(hr))
        {
            CComVariant vXmlSchema(spXmlSchema);
            CComBSTR bNull("");
            hr = spXmlSchemaColl->add(bNull, vXmlSchema);
        }
        if (SUCCEEDED(hr))
        {
            CComVariant vSchemaCache(spXmlSchemaColl);
            hr = spXmlDoc->putref_schemas(vSchemaCache);
        }
        if (SUCCEEDED(hr))
        {
            VARIANT_BOOL fvIsOk;
            CComVariant vPath(pszPath);
            hr = spXmlDoc->load(vPath, &fvIsOk);
            if (FAILED(hr) || fvIsOk != VARIANT_TRUE)
            {
                hr = spXmlDoc->get_parseError(&spXmlParseError);
                if (SUCCEEDED(hr))
                {
                    ReportXmlError("profile", spXmlParseError);
                }
                hr = E_FAIL;
            }
        }

        // now parse the specification, if correct
        if (SUCCEEDED(hr))
        {
            bool fVerbose;
            hr = _GetVerbose(spXmlDoc, &fVerbose);
            if (SUCCEEDED(hr) && (hr != S_FALSE))
            {
                pProfile->SetVerbose(fVerbose);
            }

            if (SUCCEEDED(hr))
            {
                DWORD dwProgress;
                hr = _GetProgress(spXmlDoc, &dwProgress);
                if (SUCCEEDED(hr) && (hr != S_FALSE))
                {
                    pProfile->SetProgress(dwProgress);
                }
            }

            if (SUCCEEDED(hr))
            {
                string sResultFormat;
                hr = _GetString(spXmlDoc, "//Profile/ResultFormat", &sResultFormat);
                if (SUCCEEDED(hr) && (hr != S_FALSE) && sResultFormat == "xml")
                {
                    pProfile->SetResultsFormat(ResultsFormat::Xml);
                }
            }

            if (SUCCEEDED(hr))
            {
                string sCreateFiles;
                hr = _GetString(spXmlDoc, "//Profile/PrecreateFiles", &sCreateFiles);
                if (SUCCEEDED(hr) && (hr != S_FALSE))
                {
                    if (sCreateFiles == "UseMaxSize")
                    {
                        pProfile->SetPrecreateFiles(PrecreateFiles::UseMaxSize);
                    }
                    else if (sCreateFiles == "CreateOnlyFilesWithConstantSizes")
                    {
                        pProfile->SetPrecreateFiles(PrecreateFiles::OnlyFilesWithConstantSizes);
                    }
                    else if (sCreateFiles == "CreateOnlyFilesWithConstantOrZeroSizes")
                    {
                        pProfile->SetPrecreateFiles(PrecreateFiles::OnlyFilesWithConstantOrZeroSizes);
                    }
                    else
                    {
                        hr = E_INVALIDARG;
                    }
                }
            }

            if (SUCCEEDED(hr))
            {
                hr = _ParseEtw(spXmlDoc, pProfile);
            }

            if (SUCCEEDED(hr))
            {
                hr = _ParseTimeSpans(spXmlDoc, pProfile);
            }
        }
    }
    if (fComInitialized)
    {
        CoUninitialize();
    }

    return SUCCEEDED(hr);
}