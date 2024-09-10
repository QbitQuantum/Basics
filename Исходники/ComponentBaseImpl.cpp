// LocaleBase
void ComponentBaseImpl::SetLocale(const WCHAR_T* loc) {
#ifndef __linux__
  _wsetlocale(LC_ALL, loc);
#else
  //We convert in char* char_locale
  //also we establish locale
  //setlocale(LC_ALL, char_locale);
#endif
}