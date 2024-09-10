HRESULT StringCbLengthW(
        LPCWSTR psz,
        size_t cbMax,
        size_t *pcb){
    size_t pcch;
    HRESULT result = StringCchLengthW(psz, cbMax / sizeof(wchar_t), &pcch);
    *pcb = pcch * sizeof(wchar_t);
    return result;
}