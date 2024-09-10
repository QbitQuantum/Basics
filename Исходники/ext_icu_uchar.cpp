Variant HHVM_STATIC_METHOD(IntlChar, getFC_NFKC_Closure, const Variant& arg) {
  GETCP(arg, cp);
  UErrorCode error = U_ZERO_ERROR;
  auto closure_len = u_getFC_NFKC_Closure(cp, nullptr, 0, &error);
  if (closure_len == 0) {
    return empty_string();
  }
  icu::UnicodeString closure;
  auto out = closure.getBuffer(closure_len + 1);
  error = U_ZERO_ERROR;
  closure_len = u_getFC_NFKC_Closure(cp, out, closure_len + 1, &error);
  if (U_FAILURE(error)) {
    s_intl_error->setError(error, "Failed getting closure");
    return false;
  }
  closure.releaseBuffer(closure_len);
  error = U_ZERO_ERROR;
  String ret(u8(closure, error));
  if (U_FAILURE(error)) {
    s_intl_error->setError(error, "Failed converting output to UTF8");
    return false;
  }
  return ret;
}