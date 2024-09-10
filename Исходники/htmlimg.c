static LONG var_to_size(const VARIANT *v)
{
    switch(V_VT(v)) {
    case VT_EMPTY:
        return 0;
    case VT_I4:
        return V_I4(v);
    case VT_BSTR: {
        LONG ret;
        HRESULT hres;

        hres = VarI4FromStr(V_BSTR(v), 0, 0, &ret);
        if(FAILED(hres)) {
            FIXME("VarI4FromStr failed: %08x\n", hres);
            return 0;
        }
        return ret;
    }
    default:
        FIXME("unsupported size %s\n", debugstr_variant(v));
    }
    return 0;
}