HRESULT 
ReadPropertyLong(
    IWiaPropertyStorage *pWiaPropertyStorage, 
    const PROPSPEC      *pPropSpec, 
    LONG                *plResult
)
{
    PROPVARIANT PropVariant;

    HRESULT hr = pWiaPropertyStorage->ReadMultiple(
        1, 
        pPropSpec, 
        &PropVariant
    );

    // Generally, the return value should be checked against S_FALSE.
    // If ReadMultiple returns S_FALSE, it means the property name or ID
    // had valid syntax, but it didn't exist in this property set, so
    // no properties were retrieved, and each PROPVARIANT structure is set 
    // to VT_EMPTY. But the following switch statement will handle this case
    // and return E_FAIL. So the caller of ReadPropertyLong does not need
    // to check for S_FALSE explicitly.

    if (SUCCEEDED(hr))
    {
        switch (PropVariant.vt)
        {
            case VT_I1:
            {
                *plResult = (LONG) PropVariant.cVal;

                hr = S_OK;

                break;
            }

            case VT_UI1:
            {
                *plResult = (LONG) PropVariant.bVal;

                hr = S_OK;

                break;
            }

            case VT_I2:
            {
                *plResult = (LONG) PropVariant.iVal;

                hr = S_OK;

                break;
            }

            case VT_UI2:
            {
                *plResult = (LONG) PropVariant.uiVal;

                hr = S_OK;

                break;
            }

            case VT_I4:
            {
                *plResult = (LONG) PropVariant.lVal;

                hr = S_OK;

                break;
            }

            case VT_UI4:
            {
                *plResult = (LONG) PropVariant.ulVal;

                hr = S_OK;

                break;
            }

            case VT_INT:
            {
                *plResult = (LONG) PropVariant.intVal;

                hr = S_OK;

                break;
            }

            case VT_UINT:
            {
                *plResult = (LONG) PropVariant.uintVal;

                hr = S_OK;

                break;
            }

            case VT_R4:
            {
                *plResult = (LONG) (PropVariant.fltVal + 0.5);

                hr = S_OK;

                break;
            }

            case VT_R8:
            {
                *plResult = (LONG) (PropVariant.dblVal + 0.5);

                hr = S_OK;

                break;
            }

            default:
            {
                hr = E_FAIL;

                break;
            }
        }
    }

    PropVariantClear(&PropVariant);

    return hr;
}