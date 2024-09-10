/// @brief 
std::string variant_to_str(const VARIANT& var)
{
    char buf[128] = { 0 };
    switch (var.vt)
    {
    case VT_NULL:
    case VT_EMPTY:
        return "NULL";
    case VT_I2:
        StringCbPrintfA(buf, sizeof(buf), "0x%x", (int16_t)var.iVal);
        return std::string(buf);
    case VT_I4:
        StringCbPrintfA(buf, sizeof(buf), "0x%x", (int32_t)var.lVal);
        return std::string(buf);
    case VT_UI1:
        StringCbPrintfA(buf, sizeof(buf), "0x%x", (uint8_t)var.cVal);
        return std::string(buf);
    case VT_UI2:
        StringCbPrintfA(buf, sizeof(buf), "0x%x", (uint16_t)var.uiVal);
        return std::string(buf);
    case VT_UI4:
        StringCbPrintfA(buf, sizeof(buf), "0x%x", (uint32_t)var.ulVal);
        return std::string(buf);
    case VT_INT:
        StringCbPrintfA(buf, sizeof(buf), "0x%x", (int32_t)var.intVal);
        return std::string(buf);
    case VT_UINT:
        StringCbPrintfA(buf, sizeof(buf), "0x%x", (uint32_t)var.uintVal);
        return std::string(buf);
    case VT_BSTR:
        return std::string(WcsToMbsEx(var.bstrVal));
    default:
        StringCbPrintfA(buf, sizeof(buf), "unknwon type (vt=0x%x)", var.vt);
        return std::string(buf);
    };
#pragma todo("complete this function...")
}