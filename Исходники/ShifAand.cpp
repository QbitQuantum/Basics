void ShiftAnd::compile(const String &pattern, bool ignoreCase) {
  m_patternLen = (int)pattern.length();
  if(m_patternLen >= 64) {
    throwException(_T("<%s> too long for shiftand-search. max length is 63"), pattern.cstr());
  }
  memset(m_mask, -1, sizeof(m_mask));
  for(int i = 0; i < m_patternLen; i++) {
    const _TUCHAR ch = pattern[i];
    m_mask[ch] &= ~((UINT64)1 << i);
    if (ignoreCase) {
      if (_istlower(ch)) {
        m_mask[_toupper(ch)] &= ~((UINT64)1 << i);
      } else if(_istupper(ch)) {
        m_mask[_tolower(ch)] &= ~((UINT64)1 << i);
      }
    }
  }
  m_s = (UINT64)1 << m_patternLen;
#ifdef _TEST_CLASS
  for(int i = 0; i < ARRAYSIZE(m_mask); i++) {
    const UINT64 mask = m_mask[i];
    if(mask != -1) {
      _tprintf(_T("mask[%c]:%s\n"), i, sprintbin(mask).cstr());
    }
  }
#endif
}