int _Locale_wctob(struct _Locale_ctype *__loc, wint_t c) {
  int _c;
  /* __c_locale __tmp = __uselocale( __loc ); */
  _c = wctob( c );
  /* __uselocale( __tmp ); */
  return _c;
}