HRESULT double_to_string(double n, jsstr_t **str)
{
    const WCHAR InfinityW[] = {'-','I','n','f','i','n','i','t','y',0};

    if(isnan(n)) {
        *str = jsstr_nan();
    }else if(isinf(n)) {
        *str = jsstr_alloc(n<0 ? InfinityW : InfinityW+1);
    }else if(is_int32(n)) {
        *str = int_to_string(n);
    }else {
        VARIANT strv, v;
        HRESULT hres;

        /* FIXME: Don't use VariantChangeTypeEx */
        V_VT(&v) = VT_R8;
        V_R8(&v) = n;
        V_VT(&strv) = VT_EMPTY;
        hres = VariantChangeTypeEx(&strv, &v, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT), 0, VT_BSTR);
        if(FAILED(hres))
            return hres;

        *str = jsstr_alloc(V_BSTR(&strv));
        SysFreeString(V_BSTR(&strv));
    }

    return *str ? S_OK : E_OUTOFMEMORY;
}