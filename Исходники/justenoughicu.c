int icu_format_number(lua_State *L) {
  double a = luaL_checknumber(L, 1);
  /* See http://www.unicode.org/repos/cldr/tags/latest/common/bcp47/number.xml
     for valid system names */
  const char* system = luaL_checkstring(L, 2);
  char locale[18]; // "@numbers=12345678";
  UChar buf[256];
  char utf8[256];
  int32_t needed;
  UErrorCode status = U_ZERO_ERROR;

  snprintf(locale, 18, "@numbers=%s", system);
  UNumberFormat* fmt = unum_open(UNUM_DECIMAL, 0, 0, locale, 0, &status);
  if(U_FAILURE(status)) {
    luaL_error(L, "Locale %s unavailable: %s", locale, u_errorName(status));
  }
  needed = unum_formatDouble(fmt, a, buf, 256, NULL, &status);
  assert(!U_FAILURE(status));
  u_austrncpy(utf8, buf, 256);
  lua_pushstring(L, utf8);
  return 1;
}