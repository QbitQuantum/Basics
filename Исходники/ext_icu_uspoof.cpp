bool c_SpoofChecker::t_issuspicious(CStrRef text, VRefParam issuesFound) {
  UErrorCode status = U_ZERO_ERROR;
  int32_t ret = uspoof_checkUTF8(
    m_spoof_checker,
    text.data(),
    text.length(),
    NULL,
    &status);
  if (U_FAILURE(status)) {
    throw Exception(
      "Could not check [%s] for security issues, error %d (%s)",
      text.c_str(), status, u_errorName(status));
  }
  issuesFound = ret;
  return ret != 0;
}