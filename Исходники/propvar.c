INT WINAPI PropVariantCompareEx(REFPROPVARIANT propvar1, REFPROPVARIANT propvar2,
    PROPVAR_COMPARE_UNIT unit, PROPVAR_COMPARE_FLAGS flags)
{
    const PROPVARIANT *propvar2_converted;
    PROPVARIANT propvar2_static;
    HRESULT hr;
    INT res=-1;

    TRACE("%p,%p,%x,%x\n", propvar1, propvar2, unit, flags);

    if (isemptyornull(propvar1))
    {
        if (isemptyornull(propvar2))
            return 0;
        return (flags & PVCF_TREATEMPTYASGREATERTHAN) ? 1 : -1;
    }

    if (isemptyornull(propvar2))
        return (flags & PVCF_TREATEMPTYASGREATERTHAN) ? -1 : 1;

    if (propvar1->vt != propvar2->vt)
    {
        hr = PropVariantChangeType(&propvar2_static, propvar2, 0, propvar1->vt);

        if (FAILED(hr))
            return -1;

        propvar2_converted = &propvar2_static;
    }
    else
        propvar2_converted = propvar2;

#define CMP_INT_VALUE(var) do { \
    if (propvar1->u.var > propvar2_converted->u.var) \
        res = 1; \
    else if (propvar1->u.var < propvar2_converted->u.var) \
        res = -1; \
    else \
        res = 0; \
    } while (0)

    switch (propvar1->vt)
    {
    case VT_I1:
        CMP_INT_VALUE(cVal);
        break;
    case VT_UI1:
        CMP_INT_VALUE(bVal);
        break;
    case VT_I2:
        CMP_INT_VALUE(iVal);
        break;
    case VT_UI2:
        CMP_INT_VALUE(uiVal);
        break;
    case VT_I4:
        CMP_INT_VALUE(lVal);
        break;
    case VT_UI4:
        CMP_INT_VALUE(uiVal);
        break;
    case VT_I8:
        CMP_INT_VALUE(hVal.QuadPart);
        break;
    case VT_UI8:
        CMP_INT_VALUE(uhVal.QuadPart);
        break;
    case VT_BSTR:
        /* FIXME: Use string flags. */
        res = lstrcmpW(propvar1->u.bstrVal, propvar2->u.bstrVal);
        break;
    default:
        FIXME("vartype %d not handled\n", propvar1->vt);
        res = -1;
        break;
    }

    if (propvar2_converted == &propvar2_static)
        PropVariantClear(&propvar2_static);

    return res;
}