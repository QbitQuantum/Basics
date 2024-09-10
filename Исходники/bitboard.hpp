  // これはコードが見難くなるけど仕方ない。
  bool andIsNot0(const Bitboard& bb) const {
#ifdef HAVE_SSE4
    return !(_mm_testz_si128(this->m_, bb.m_));
#else
    return (*this & bb).isNot0();
#endif
  }