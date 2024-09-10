Variant c_Collator::t_compare(CStrRef str1, CStrRef str2) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Collator, Collator::compare);
  if (!m_ucoll) {
    raise_warning("compare called on uninitialized Collator object");
    return 0;
  }
  UChar* ustr1 = NULL;
  UChar* ustr2 = NULL;
  int ustr1_len = 0;
  int ustr2_len = 0;
  m_errcode.clear();
  intl_convert_utf8_to_utf16(&ustr1, &ustr1_len,
                             str1.data(), str1.length(),
                             &(m_errcode.code));
  if (U_FAILURE(m_errcode.code)) {
    free(ustr1);
    return false;
  }
  intl_convert_utf8_to_utf16(&ustr2, &ustr2_len,
                             str2.data(), str2.length(),
                             &(m_errcode.code));
  if (U_FAILURE(m_errcode.code)) {
    free(ustr1);
    free(ustr2);
    return false;
  }
  int64 ret = ucol_strcoll(m_ucoll, ustr1, ustr1_len, ustr2, ustr2_len);
  free(ustr1);
  free(ustr2);
  return ret;
}