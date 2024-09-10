void c_EncodingDetector::t_setdeclaredencoding(CStrRef text) {
  INSTANCE_METHOD_INJECTION_BUILTIN(EncodingDetector, EncodingDetector::setdeclaredencoding);
  UErrorCode status = U_ZERO_ERROR;
  ucsdet_setDeclaredEncoding(
    m_encoding_detector,
    text.data(),
    text.length(),
    &status);
  if (U_FAILURE(status)) {
    throw Exception(
      "Could not set encoding detector declared encoding to [%s], error %d (%s)",
      text.c_str(), status, u_errorName(status));
  }
}