STDMETHODIMP C_ECBLoader::get_Styles(STRING_ARRAY *pVal)
{
    if (!pVal) {
        return E_POINTER;
    }

    try {

        if (*pVal) {
            SafeArrayDestroy(*pVal);
        }

        int len = styles.GetLength();

        SAFEARRAYBOUND rgsabound[] = { len, 0 };
        SAFEARRAY* psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

        BSTR *bs;

        SafeArrayAccessData(psa, (LPVOID*)&bs);

        for (int n = 0; n < len; n++) {
            *bs++ = styles[n]->toBSTR();
        }

        SafeArrayUnaccessData(psa);

        SafeArrayCopy(psa, pVal);
        SafeArrayDestroy(psa);
    }
    catch (C_STLNonStackException const &exception) {
        exception.Log(_T("Exception in C_ECBLoader::get_Styles"));
    }


    return S_OK;
}