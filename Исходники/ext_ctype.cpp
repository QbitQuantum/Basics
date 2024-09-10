bool HHVM_FUNCTION(ctype_cntrl, CVarRef text) {
  return ctype(text, [] (int i) -> int { return iscntrl(i); });
}