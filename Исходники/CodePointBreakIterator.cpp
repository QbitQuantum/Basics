CodePointBreakIterator&
CodePointBreakIterator::refreshInputText(UText *input,
           UErrorCode &status) {
  if (U_FAILURE(status)) {
    return *this;
  }
  if (!input) {
    status = U_ILLEGAL_ARGUMENT_ERROR;
    return *this;
  }

  int64_t pos = utext_getNativeIndex(m_text);
  m_text = utext_clone(m_text, input, false, true, &status);
  if (U_FAILURE(status)) {
    return *this;
  }

  utext_setNativeIndex(m_text, pos);
  if (utext_getNativeIndex(m_text) != pos) {
    status = U_ILLEGAL_ARGUMENT_ERROR;
  }

  return *this;
}