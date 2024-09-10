JsErrorCode StringifyJsTypedArray(JsValueRef value)
{
    JsTypedArrayType arrayType;
    JsValueRef arrayBuffer;
    UINT byteOffset, byteLength;
    IfFailRet(JsGetTypedArrayInfo(value, &arrayType, &arrayBuffer, &byteOffset, &byteLength));

    switch (arrayType)
    {
    case JsArrayTypeInt8:
        OutputDebugStringW(L"Int8Array ");
        break;
    case JsArrayTypeUint8:
        OutputDebugStringW(L"Uint8Array ");
        break;
    case JsArrayTypeUint8Clamped:
        OutputDebugStringW(L"Uint8ClampedArray ");
        break;
    case JsArrayTypeInt16:
        OutputDebugStringW(L"Int16Array ");
        break;
    case JsArrayTypeUint16:
        OutputDebugStringW(L"Uint16Array ");
        break;
    case JsArrayTypeInt32:
        OutputDebugStringW(L"Int32Array ");
        break;
    case JsArrayTypeUint32:
        OutputDebugStringW(L"Uint32Array ");
        break;
    case JsArrayTypeFloat32:
        OutputDebugStringW(L"Float32Array ");
        break;
    case JsArrayTypeFloat64:
        OutputDebugStringW(L"Float64Array ");
        break;
    }

    JsPropertyIdRef lengthId;
    JsValueRef lengthProp;
    int lengthValue;
    IfFailRet(JsGetPropertyIdFromName(L"length", &lengthId));
    IfFailRet(JsGetProperty(value, lengthId, &lengthProp));
    IfFailRet(JsNumberToInt(lengthProp, &lengthValue));

    OutputDebugStringW(L"[ ");

    for (int i = 0; i < lengthValue; i++)
    {
        if (i == DEFAULT_ARRAY_MAX_LENGTH)
        {
            OutputDebugStringW(DEFAULT_TRUNCATED_VALUE);
            break;
        }

        JsValueRef index, indexResult;
        IfFailRet(JsIntToNumber(i, &index));
        IfFailRet(JsGetIndexedProperty(value, index, &indexResult));
        IfFailRet(StringifyToString(indexResult));

        if (i != lengthValue - 1)
        {
            OutputDebugStringW(L", ");
        }
        else
        {
            OutputDebugStringW(L" ");
        }
    }

    OutputDebugStringW(L"]");

    return JsNoError;
}