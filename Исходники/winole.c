wchar_t *Date2String(DATE date){
    wchar_t *buf;
    SYSTEMTIME st;

    VariantTimeToSystemTime(date, &st);
    buf = (wchar_t*)malloc(20 * sizeof(wchar_t));
    //swprintf(buf,L"%04d/%02d/%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
    return buf;
}