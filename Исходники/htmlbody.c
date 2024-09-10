static BOOL variant_to_nscolor(const VARIANT *v, nsAString *nsstr)
{
    switch(V_VT(v)) {
    case VT_BSTR:
        nsAString_Init(nsstr, V_BSTR(v));
        return TRUE;

    case VT_I4: {
        PRUnichar buf[10];
        static const WCHAR formatW[] = {'#','%','x',0};

        wsprintfW(buf, formatW, V_I4(v));
        nsAString_Init(nsstr, buf);
        return TRUE;
    }

    default:
        FIXME("invalid color %s\n", debugstr_variant(v));
    }

    return FALSE;

}