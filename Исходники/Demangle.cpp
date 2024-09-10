// The <seq-id> is a sequence number in base 36,
// using digits and upper case letters
static bool ParseSeqId(State *state) {
  const char *p = state->mangled_cur;
  for (;*p != '\0'; ++p) {
    if (!IsDigit(*p) && !(*p >= 'A' && *p <= 'Z')) {
      break;
    }
  }
  if (p != state->mangled_cur) {  // Conversion succeeded.
    state->mangled_cur = p;
    return true;
  }
  return false;
}