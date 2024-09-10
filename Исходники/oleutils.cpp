WXDLLEXPORT bool wxConvertVariantToOle(const wxVariant& variant, VARIANTARG& oleVariant)
{
    VariantInit(&oleVariant);
    if (variant.IsNull())
    {
        oleVariant.vt = VT_NULL;
        return true;
    }

    wxString type(variant.GetType());


    if (type == wxT("long"))
    {
        oleVariant.vt = VT_I4;
        oleVariant.lVal = variant.GetLong() ;
    }
    // Original VC6 came with SDK too old to contain VARIANT::llVal declaration
    // and there doesn't seem to be any way to test for it as Microsoft simply
    // added it to the later version of oaidl.h without changing anything else.
    // So assume it's not present for VC6, even though it might be if an
    // updated SDK is used. In this case the user would need to disable this
    // check himself.
#if wxUSE_LONGLONG && !defined(__VISUALC6__)
    else if (type == wxT("longlong"))
    {
        oleVariant.vt = VT_I8;
        oleVariant.llVal = variant.GetLongLong().GetValue();
    }
#endif
    else if (type == wxT("char"))
    {
        oleVariant.vt=VT_I1;            // Signed Char
        oleVariant.cVal=variant.GetChar();
    }
    else if (type == wxT("double"))
    {
        oleVariant.vt = VT_R8;
        oleVariant.dblVal = variant.GetDouble();
    }
    else if (type == wxT("bool"))
    {
        oleVariant.vt = VT_BOOL;
        oleVariant.boolVal = variant.GetBool() ? VARIANT_TRUE : VARIANT_FALSE;
    }
    else if (type == wxT("string"))
    {
        wxString str( variant.GetString() );
        oleVariant.vt = VT_BSTR;
        oleVariant.bstrVal = wxConvertStringToOle(str);
    }
#if wxUSE_DATETIME
    else if (type == wxT("datetime"))
    {
        wxDateTime date( variant.GetDateTime() );
        oleVariant.vt = VT_DATE;

        SYSTEMTIME st;
        date.GetAsMSWSysTime(&st);

        SystemTimeToVariantTime(&st, &oleVariant.date);
    }
#endif
    else if (type == wxT("void*"))
    {
        oleVariant.vt = VT_DISPATCH;
        oleVariant.pdispVal = (IDispatch*) variant.GetVoidPtr();
    }
    else if (type == wxT("list"))
    {
        wxSafeArrayHelper sah;

        if (!sah.Create(VT_VARIANT, variant.GetCount()))
            return false;

        for (size_t i = 0; i < variant.GetCount(); i++)
        {
            if (!sah.SetElement(i, variant[i]))
                return false;
        }

        oleVariant.vt = VT_VARIANT | VT_ARRAY;
        oleVariant.parray = sah.Detach();
    }
    else if (type == wxT("arrstring"))
    {
        wxArrayString strings(variant.GetArrayString());
        wxSafeArrayHelper sah;

        if (!sah.Create(VT_BSTR, strings.GetCount()))
            return false;

        for (size_t i = 0; i < strings.GetCount(); i++)
        {
            if (!sah.SetElement(i, strings[i]))
                return false;
        }

        oleVariant.vt = VT_BSTR | VT_ARRAY;
        oleVariant.parray = sah.Detach();
    }
    else
    {
        oleVariant.vt = VT_NULL;
        return false;
    }
    return true;
}