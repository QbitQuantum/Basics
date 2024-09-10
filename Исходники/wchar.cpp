size_t mbrtowc(wchar_t* pwc, const char* s, size_t n, mbstate_t* ps) {
  static mbstate_t __private_state;
  mbstate_t* state = (ps == NULL) ? &__private_state : ps;

  // We should never get to a state which has all 4 bytes of the sequence set.
  // Full state verification is done when decoding the sequence (after we have
  // all the bytes).
  if (mbstate_get_byte(state, 3) != 0) {
    return reset_and_return_illegal(EINVAL, state);
  }

  if (s == NULL) {
    s = "";
    n = 1;
    pwc = NULL;
  }

  if (n == 0) {
    return 0;
  }

  uint8_t ch;
  if (mbsinit(state) && (((ch = static_cast<uint8_t>(*s)) & ~0x7f) == 0)) {
    // Fast path for plain ASCII characters.
    if (pwc != NULL) {
      *pwc = ch;
    }
    return (ch != '\0' ? 1 : 0);
  }

  // Determine the number of octets that make up this character
  // from the first octet, and a mask that extracts the
  // interesting bits of the first octet. We already know
  // the character is at least two bytes long.
  size_t length;
  int mask;

  // We also specify a lower bound for the character code to
  // detect redundant, non-"shortest form" encodings. For
  // example, the sequence C0 80 is _not_ a legal representation
  // of the null character. This enforces a 1-to-1 mapping
  // between character codes and their multibyte representations.
  wchar_t lower_bound;

  // The first byte in the state (if any) tells the length.
  size_t bytes_so_far = mbstate_bytes_so_far(state);
  ch = bytes_so_far > 0 ? mbstate_get_byte(state, 0) : static_cast<uint8_t>(*s);
  if ((ch & 0x80) == 0) {
    mask = 0x7f;
    length = 1;
    lower_bound = 0;
  } else if ((ch & 0xe0) == 0xc0) {
    mask = 0x1f;
    length = 2;
    lower_bound = 0x80;
  } else if ((ch & 0xf0) == 0xe0) {
    mask = 0x0f;
    length = 3;
    lower_bound = 0x800;
  } else if ((ch & 0xf8) == 0xf0) {
    mask = 0x07;
    length = 4;
    lower_bound = 0x10000;
  } else {
    // Malformed input; input is not UTF-8. See RFC 3629.
    return reset_and_return_illegal(EILSEQ, state);
  }

  // Fill in the state.
  size_t bytes_wanted = length - bytes_so_far;
  size_t i;
  for (i = 0; i < MIN(bytes_wanted, n); i++) {
    if (!mbsinit(state) && ((*s & 0xc0) != 0x80)) {
      // Malformed input; bad characters in the middle of a character.
      return reset_and_return_illegal(EILSEQ, state);
    }
    mbstate_set_byte(state, bytes_so_far + i, *s++);
  }
  if (i < bytes_wanted) {
    return ERR_INCOMPLETE_SEQUENCE;
  }

  // Decode the octet sequence representing the character in chunks
  // of 6 bits, most significant first.
  wchar_t wch = mbstate_get_byte(state, 0) & mask;
  for (i = 1; i < length; i++) {
    wch <<= 6;
    wch |= mbstate_get_byte(state, i) & 0x3f;
  }

  if (wch < lower_bound) {
    // Malformed input; redundant encoding.
    return reset_and_return_illegal(EILSEQ, state);
  }
  if ((wch >= 0xd800 && wch <= 0xdfff) || wch == 0xfffe || wch == 0xffff) {
    // Malformed input; invalid code points.
    return reset_and_return_illegal(EILSEQ, state);
  }
  if (pwc != NULL) {
    *pwc = wch;
  }
  return reset_and_return(wch == L'\0' ? 0 : bytes_wanted, state);
}