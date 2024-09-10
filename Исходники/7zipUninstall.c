static LONG MyRegistry_DeleteKey_32(HKEY parentKey, LPCWSTR name)
{
#if k_Reg_WOW_Flag_32 != 0
    if (func_RegDeleteKeyExW)
        return func_RegDeleteKeyExW(parentKey, name, k_Reg_WOW_Flag_32, 0);
    return E_FAIL;
#else
    return RegDeleteKeyW(parentKey, name);
#endif
}