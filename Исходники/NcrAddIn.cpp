//---------------------------------------------------------------------------//
void CAddInNCR5976::SetLocale(const WCHAR_T* loc)
{
    Debug::log("CAddInNCR5976::SetLocale");
    _wsetlocale(LC_ALL, loc);