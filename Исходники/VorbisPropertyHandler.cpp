//---------------------------Start InitPropVariantFromCString----------------------//
inline HRESULT InitPropVariantFromCString (__in PCSTR psz, __out PROPVARIANT *ppropvar) {
      const size_t cSize = strlen (psz) + 1;
      std::wstring wc (cSize, L'#');
      mbstowcs (&wc[0], psz, cSize);

      return InitPropVariantFromString (wc.c_str (), ppropvar);
}