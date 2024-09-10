HRESULT ContentStudioProperties::GetStringW(LPCSTR id, LPWSTR pvalue, size_t cch)
{
    HRESULT hr = S_OK;
    _variant_t v;
    _bstr_t bstr;

    hr = Get(id, v);
    if (SUCCEEDED(hr))
    {
        bstr = v;
        std::wstring s = stde::to_wstring(bstr);
        hr = StringCchCopyW(pvalue, cch, s.c_str());
    }

    return hr;
}