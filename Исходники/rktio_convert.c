int rktio_strcoll_utf16(rktio_t *rktio,
                        rktio_char16_t *s1, intptr_t l1,
                        rktio_char16_t *s2, intptr_t l2,
                        rktio_bool_t cvt_case)
{
#ifdef MACOS_UNICODE_SUPPORT
  CFStringRef str1, str2;
  CFComparisonResult r;

  str1 = CFStringCreateWithBytes(NULL, (unsigned char *)s1, (l1 * sizeof(rktio_char16_t)), 
				 kCFStringEncodingUnicode, FALSE);
  str2 = CFStringCreateWithBytes(NULL, (unsigned char *)s2, (l2 * sizeof(rktio_char16_t)), 
				 kCFStringEncodingUnicode, FALSE);

  r = CFStringCompare(str1, str2, (kCFCompareLocalized
				   | (cvt_case ? kCFCompareCaseInsensitive : 0)));

  CFRelease(str1);
  CFRelease(str2);

  return (int)r;
#elif defined(RKTIO_SYSTEM_WINDOWS)
  int r;
  r = CompareStringW(LOCALE_USER_DEFAULT,
		     ((cvt_case ? NORM_IGNORECASE : 0)
		      | NORM_IGNOREKANATYPE
		      | NORM_IGNOREWIDTH),
		     (wchar_t *)s1, l1, (wchar_t *)s2, l2);
  
  return r - 2;
#else
  return 0;
#endif
}